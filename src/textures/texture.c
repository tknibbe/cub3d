/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:10:57 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/15 17:10:48 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	buffer_to_img(int *buffer, mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(img, x, y, buffer[x * HEIGHT + y]);
			y++;
		}
		x++;
	}
}

static void	draw_wall(t_ray ray, t_game *game, int *buffer, int x)
{
	if (ray.side == 0)
		ray.wallx = game->player.pos.y + ray.dist_to_wall * ray.ray.y;
	else
		ray.wallx = game->player.pos.x + ray.dist_to_wall * ray.ray.x;
	ray.wallx -= floor(ray.wallx);
	ray.texx = (int)(ray.wallx * (double)ray.tex_width);
	if (ray.side == 0 && ray.ray.x > 0)
		ray.texx = ray.tex_width - ray.texx -1;
	if (ray.side == 1 && ray.ray.y < 0)
		ray.texx = ray.tex_width - ray.texx - 1;
	ray.step = (double) ray.tex_height / ray.wall_height;
	ray.texpos = (ray.wall_start - HALF_HEIGHT + ray.wall_height / 2) * ray.step;
	while (ray.y < ray.wall_end)
	{
		ray.texy = (int)ray.texpos;
		ray.texpos += ray.step;
		ray.colour = ((int *)ray.texture->pixels) \
					[(ray.tex_height * ray.texy + ray.texx)];
		buffer[x * HEIGHT + ray.y] = ray.colour;
		ray.y++;
	}
}

static void	set_texture(t_ray *ray, mlx_texture_t *text)
{
	ray->texture = text;
	ray->tex_height = text->height;
	ray->tex_width = text->width;
}

static void	set_texture_direction(t_game *game, t_ray *ray)
{
	if (ray->door)
		set_texture(ray, game->textures.door);
	else if (ray->side == 0 && ray->ray.x < 0)
		set_texture(ray, game->textures.west);
	else if (ray->side == 0 && ray->ray.x >= 0)
		set_texture(ray, game->textures.east);
	else if (ray->side == 1 && ray->ray.y < 0)
		set_texture(ray, game->textures.north);
	else
		set_texture(ray, game->textures.south);
}

void	line_to_buffer(int *buffer, t_game *game, t_ray ray_vars, int x)
{
	ray_vars.y = 0;
	ray_vars.wall_height = (int)(HEIGHT / ray_vars.dist_to_wall);
	ray_vars.wall_start = -ray_vars.wall_height / 2 + HALF_HEIGHT;
	if (ray_vars.wall_start < 0)
		ray_vars.wall_start = 0;
	ray_vars.wall_end = ray_vars.wall_height / 2 + HALF_HEIGHT;
	if (ray_vars.wall_end >= HEIGHT)
		ray_vars.wall_end = HEIGHT - 1;
	set_texture_direction(game, &ray_vars);
	while (ray_vars.y < ray_vars.wall_start)
	{
		buffer[x * HEIGHT + ray_vars.y] = game->textures.ceiling;
		ray_vars.y++;
	}
	draw_wall(ray_vars, game, buffer, x);
	ray_vars.y = ray_vars.wall_end;
	while (ray_vars.y < HEIGHT)
	{
		buffer[x * HEIGHT + ray_vars.y] = game->textures.floor;
		ray_vars.y++;
	}
}

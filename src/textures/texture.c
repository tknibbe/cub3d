/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:10:57 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/25 18:58:00 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#include <stdio.h> //debug
#include <unistd.h>

#define RED		0xFF0000FF
#define GREEN	0x00FF00FF

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

static void	draw_wall(t_ray ray, t_game *game, int *y, int *buffer, int x) //fix input to struct
{
	double Wallx;

	if (ray.side == 0)
		Wallx = game->player.pos.y + ray.dist_to_wall * ray.ray.y;
	else
		Wallx = game->player.pos.x + ray.dist_to_wall * ray.ray.x;
	Wallx -= floor(Wallx);
	// printf("final wallx = %f\n", Wallx);

	//adjust code here to pick correct texture
	int texx = (int) (Wallx * (double) ray.tex_width);
	if (ray.side == 0 && ray.ray.x > 0)
		texx = ray.tex_width - texx -1;
	if (ray.side == 1 && ray.ray.y < 0)
		texx = ray.tex_width - texx - 1;
	// printf ("wall is hit at %f\nx in texture is %d (out of %d)\n", Wallx, texx, game->textures.north->width);
	
	
	double step = (double) ray.tex_height / ray.wall_height; // why 1.0 *?

	// printf("%f vs %d\n", 1.0 * ray.tex_height / ray.wall_height, ray.tex_height / ray.wall_height);
	double texPos = (ray.wall_start - HEIGHT / 2 + ray.wall_height / 2) * step;

	
	uint32_t colour; 
	while (*y < ray.wall_end)
	{
		colour = 0;
		int texy = (int)texPos;
		texPos += step;
		colour |= ray.texture->pixels[(ray.tex_height * texy + texx) * 4] << 24;
		colour |= ray.texture->pixels[(ray.tex_height * texy + texx) * 4 + 1] << 16;
		colour |= ray.texture->pixels[(ray.tex_height * texy + texx) * 4 + 2] << 8;
		colour |= ray.texture->pixels[(ray.tex_height * texy + texx) * 4 + 3];
		// if (ray.side == 1)
		// 	colour = (colour >> 1) & 8355711;
		buffer[x * HEIGHT + *y] = colour;
		*y += 1;
	}
}

static void	set_texture_direction(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->ray.x < 0)
	{
		ray->texture = game->textures.west;
		ray->tex_height = game->textures.west->height;
		ray->tex_width = game->textures.west->width;
	}
	else if (ray->side == 0 && ray->ray.x >= 0)
	{
		ray->texture = game->textures.east;
		ray->tex_height = game->textures.east->height;
		ray->tex_width = game->textures.east->width;
	}
	else if (ray->side == 1 && ray->ray.y < 0)
	{
		ray->texture = game->textures.north;
		ray->tex_height = game->textures.north->height;
		ray->tex_width = game->textures.north->width;
	}
	else
	{
		ray->texture = game->textures.south;
		ray->tex_height = game->textures.south->height;
		ray->tex_width = game->textures.south->width;
	}
}

void	line_to_buffer(int *buffer, t_game *game, t_ray ray_vars, int x)
{
	int	y;

	y = 0;

	ray_vars.wall_height = (int)(HEIGHT / ray_vars.dist_to_wall);
	ray_vars.wall_start = -ray_vars.wall_height / 2 + HEIGHT / 2;
	if (ray_vars.wall_start < 0)
		ray_vars.wall_start = 0;
	ray_vars.wall_end = ray_vars.wall_height / 2 + HEIGHT / 2;
	if (ray_vars.wall_end >= HEIGHT)
		ray_vars.wall_end = HEIGHT - 1;
	
	set_texture_direction(game, &ray_vars);
	while (y < ray_vars.wall_start)
	{
		buffer[x * HEIGHT + y] = game->textures.ceiling;
		y++;
	}
	draw_wall(ray_vars, game, &y, buffer, x);
	while (y < HEIGHT)
	{
		buffer[x * HEIGHT + y] = game->textures.floor;
		y++;
	}
}
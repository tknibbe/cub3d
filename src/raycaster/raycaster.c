/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:43:37 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/02/15 17:24:40 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	buffer_to_img(int *buffer, mlx_image_t *img)
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

static void	dda(t_ray *ray_vars, t_game *game)
{
	int	hit;

	hit = 0;
	ray_vars->door = 0;
	while (hit == 0 && ray_vars->door == 0)
	{
		if (ray_vars->side_dist.x < ray_vars->side_dist.y)
		{
			ray_vars->side_dist.x += ray_vars->block_dist.x;
			ray_vars->map_x += (int)ray_vars->step_dir_x;
			ray_vars->side = 0;
		}
		else
		{
			ray_vars->side_dist.y += ray_vars->block_dist.y;
			ray_vars->map_y += (int)ray_vars->step_dir_y;
			ray_vars->side = 1;
		}
		if (game->map[ray_vars->map_y][ray_vars->map_x] == '1')
			hit = 1;
		if (game->map[ray_vars->map_y][ray_vars->map_x] == '2')
			ray_vars->door = 1;
	}
}

void	ray_caster(t_game *game)
{
	int		screen_x;
	t_ray	ray_var;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		setup_ray_vars(&ray_var, game->player, screen_x);
		dda(&ray_var, game);
		if (ray_var.side == 0)
			ray_var.dist_to_wall = ray_var.side_dist.x - ray_var.block_dist.x;
		else
			ray_var.dist_to_wall = ray_var.side_dist.y - ray_var.block_dist.y;
		game->wall_distances[screen_x] = ray_var.dist_to_wall;
		line_to_buffer(game, ray_var, screen_x);
		screen_x++;
	}
	buffer_to_img(game->img_buffer, game->images.maze);
}

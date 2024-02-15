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
#include "libft.h"

static void	dda(t_ray *ray_vars, t_game *game)
{
	int hit;

	hit = 0;
	ray_vars->door = 0;
	while (hit == 0)
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
		if (game->map[ray_vars->map_y][ray_vars->map_x] == '2') // door
		{
			ray_vars->door = 1;
			hit = 1;
		}
	}
}

void	ray_caster(t_game *game)
{
	int		screen_x;
	t_ray	ray_vars;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		setup_ray_vars(&ray_vars, game->player, screen_x);
		dda(&ray_vars, game);
		if (ray_vars.side == 0)
			ray_vars.dist_to_wall = (ray_vars.side_dist.x - ray_vars.block_dist.x);
		else
			ray_vars.dist_to_wall = (ray_vars.side_dist.y - ray_vars.block_dist.y);
		game->wall_distances[screen_x] = ray_vars.dist_to_wall;
		// draw_line(ray_vars, game, screen_x);
		line_to_buffer(game, ray_vars, screen_x);
		screen_x++;
	}
	buffer_to_img(game->img_buffer, game->images.maze);
	// mlx_image_to_window(game->mlx, game->images.maze, 0, 0);
}

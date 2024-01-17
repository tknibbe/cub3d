/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:43:37 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/13 18:43:38 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	set_block_distance(t_ray *ray_vars, t_player player)
{
	if (ray_vars->ray.x == 0)
		ray_vars->block_dist.x = 1000000000;
	else
		ray_vars->block_dist.x = fabs(1 / ray_vars->ray.x);
	if (ray_vars->ray.y == 0)
		ray_vars->block_dist.y = 1000000000;
	else
		ray_vars->block_dist.y = fabs(1 / ray_vars->ray.y);
}

static void	set_start_dist_to_block(t_ray *ray_vars, t_player player)
{
	if (ray_vars->ray.x < 0)
	{
		ray_vars->step_dir_x = -1;
		ray_vars->side_dist.x = (player.pos.x - ray_vars->map_x) * ray_vars->block_dist.x;
	}
	else
	{
		ray_vars->step_dir_x = 1;
		ray_vars->side_dist.x = (ray_vars->map_x + 1 - player.pos.x) * ray_vars->block_dist.x;
	}
	if (ray_vars->ray.y < 0)
	{
		ray_vars->step_dir_y = -1;
		ray_vars->side_dist.y = (player.pos.y - ray_vars->map_y) * ray_vars->block_dist.y;
	}
	else
	{
		ray_vars->step_dir_y = 1;
		ray_vars->side_dist.y = (ray_vars->map_y + 1 - player.pos.y) * ray_vars->block_dist.y;
	}
}

static void	setup_ray_vars(t_ray *ray_vars, t_player player, int screen_x)
{
	ray_vars->camerax = ((double)(2 * screen_x) / WIDTH) - 1;
	ray_vars->ray.x = player.dir.x + player.plane.x * ray_vars->camerax;
	ray_vars->ray.y = player.dir.y + player.plane.y * ray_vars->camerax;
	ray_vars->map_x = (int)player.pos.x;
	ray_vars->map_y = (int)player.pos.y;
	set_block_distance(ray_vars, player);
	set_start_dist_to_block(ray_vars, player);
}

static void	dda(t_ray *ray_vars, t_game *game)
{
//	printf("%d\n")
	int hit;

	hit = 0;
	while (game->map[ray_vars->map_y][ray_vars->map_x] == '0')
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
//		if (game->map[ray_vars->map_y][ray_vars->map_x] > '0')
//			hit = 1;
	}
}

void	draw_line(t_ray ray_vars, t_game *game, int screen_x)
{
	int	wall_height;
	int	start_y;
	int	end_y;
	int	y;

	wall_height = (int)(HEIGHT / ray_vars.dist_to_wall);
//	printf("%lf, %d\n",ray_vars.dist_to_wall, wall_height);
	start_y = -wall_height / 2 + HEIGHT / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = wall_height / 2 + HEIGHT / 2;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;

	//	printf("%d, %d\n", start_y, end_y);
	y = 0;
	while (y < start_y)
	{
		mlx_put_pixel(game->images.maze, screen_x, y, game->textures.ceiling);
		y++;
	}
	while (y <= end_y)
	{
		mlx_put_pixel(game->images.maze, screen_x, y, 0x00FF00FF);
		y++;
	}
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->images.maze, screen_x, y, game->textures.floor);
		y++;
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
		draw_line(ray_vars, game, screen_x);
		screen_x++;
	}
}

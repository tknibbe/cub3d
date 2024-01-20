/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/13 18:43:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/01/18 13:18:37 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda(t_ray *ray_vars, t_game *game)
{
	int hit;

	hit = 0;
	(void)hit;
//	hit = 0;
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
		if (game->map[ray_vars->map_y][ray_vars->map_x] > '0')
			hit = 1;
	}
}

// add bresserham
void	draw_line(t_ray ray_vars, t_game *game, int screen_x)
{
	int	wall_height;
	int	start_y;
	int	end_y;
	int	y;

	wall_height = (int)(HEIGHT / ray_vars.dist_to_wall);
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

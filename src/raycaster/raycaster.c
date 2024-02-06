/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:43:37 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/02/05 13:05:53 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	dda(t_ray *ray_vars, t_game *game)
{
	int hit;

	hit = 0;
	if (ray_vars->door)
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

// add bresserham
// void	draw_line(t_ray ray_vars, t_game *game, int screen_x)
// {
// 	int	wall_height;
// 	int	start_y;
// 	int	end_y;
// 	int	y;

// 	wall_height = (int)(HEIGHT / ray_vars.dist_to_wall);
// 	start_y = -wall_height / 2 + HEIGHT / 2;
// 	if (start_y < 0)
// 		start_y = 0;
// 	end_y = wall_height / 2 + HEIGHT / 2;
// 	if (end_y >= HEIGHT)
// 		end_y = HEIGHT - 1;

// 	//	printf("%d, %d\n", start_y, end_y);

// 	//calculate the buffer here, including the floor and ceiling, and then put_pixel the whole thing

// 	y = 0;
// 	while (y < start_y)
// 	{
// 		mlx_put_pixel(game->images.maze, screen_x, y, game->textures.ceiling);
// 		y++;
// 	}
// 	while (y <= end_y)
// 	{
// 		mlx_put_pixel(game->images.maze, screen_x, y, buffer[screen_x], y);
// 		y++;
// 	}
// 	while (y < HEIGHT)
// 	{
// 		mlx_put_pixel(game->images.maze, screen_x, y, game->textures.floor);
// 		y++;
// 	}
// }

void	ray_caster(t_game *game)
{
	int		screen_x;
	t_ray	ray_vars;
	int		buffer[WIDTH * HEIGHT]; //change to malloc at least
	// int		*buffer = malloc(sizeof(uint32_t) * (WIDTH * HEIGHT));//	[WIDTH * HEIGHT]; //change to malloc at least

	// ft_memset(buffer, 0x00FF00, sizeof(uint32_t) * WIDTH * HEIGHT);
	screen_x = 0;
	while (screen_x < WIDTH)
	{
		setup_ray_vars(&ray_vars, game->player, screen_x);
		dda(&ray_vars, game);
		if (ray_vars.side == 0)
			ray_vars.dist_to_wall = (ray_vars.side_dist.x - ray_vars.block_dist.x);
		else
			ray_vars.dist_to_wall = (ray_vars.side_dist.y - ray_vars.block_dist.y);
		// draw_line(ray_vars, game, screen_x);
		line_to_buffer(buffer, game, ray_vars, screen_x);
		screen_x++;
	}
	buffer_to_img(buffer, game->images.maze);
	// mlx_image_to_window(game->mlx, game->images.maze, 0, 0);
	// free(buffer);
}

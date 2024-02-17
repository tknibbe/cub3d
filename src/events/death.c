/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/17 16:37:56 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/17 16:37:56 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#define ENEMY '4'

void	check_death(t_game *game)
{
	int			map_x;
	int			map_y;
	mlx_image_t	*you_lost;

	map_x = (int)game->player.pos.x;
	map_y = (int)game->player.pos.y;

	if (game->map[map_y][map_x] == ENEMY && \
		(fabs((double)map_x + 0.5 - game->player.pos.x) < 0.25 && \
		fabs((double)map_y + 0.5 - game->player.pos.y) < 0.25))
	{
		you_lost = mlx_put_string(game->mlx, "lol you lost", HALF_WIDTH, HALF_HEIGHT);
		mlx_resize_image(you_lost, 500, 200);
		mlx_set_instance_depth(you_lost->instances, 2);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:27:39 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/25 19:11:14 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	set_plane(t_player *player)
{
	if (player->dir.x == -1)
	{
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else if (player->dir.x == 1)
	{
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (player->dir.y == -1)
	{
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else
	{
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
}

double	fov(double a, double b)
{
	double	length;

	length = sqrt(a * a + b * b);
	return (2 * atan(length) * 180 / PI);
}

void	initialise_player(t_game *game)
{
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.02;
	game->player.has_moved = true;
	set_plane(&game->player);
	game->player.fov = fov(game->player.plane.x, game->player.plane.y);
	printf("%lf\n", game->player.fov);
}

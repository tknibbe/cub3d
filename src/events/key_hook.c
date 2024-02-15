/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:30:45 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/15 15:21:12 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DOOR_CLOSED '2'
#define DOOR_OPENED '3'

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_MINUS) && game->player.fov > 50)
	{
		game->player.plane.x *= 0.95;
		game->player.plane.y *= 0.95;
		game->player.fov = fov(game->player.plane.x, game->player.plane.y);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_EQUAL) && game->player.fov < 100)
	{
		game->player.plane.x *= 1.05;
		game->player.plane.y *= 1.05;
		game->player.fov = fov(game->player.plane.x, game->player.plane.y);
	}

	game = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		if (door_status(game->map, game->player.pos, DOOR_CLOSED))
			open_door(game->map, game->player.pos);
		else if (door_status(game->map, game->player.pos, DOOR_OPENED))
			close_door(game->map, game->player.pos);
		game->player.has_moved = true;
	}
}

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
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		if (door_status(game->map, game->player.pos, DOOR_CLOSED))
			open_door(game->map, game->player.pos);
		else if (door_status(game->map, game->player.pos, DOOR_OPENED))
			close_door(game->map, game->player.pos);
		game->player.has_moved = true;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

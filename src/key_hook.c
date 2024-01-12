/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:46:29 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/13 17:03:43 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(void *param)
{
	t_game *game = param; //change parameters here so we can free our data when ES is pressed


	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.x -= 5;
		game->images.player->instances[0].x -= 5;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.x += 5;
		game->images.player->instances[0].x += 5;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->player.y -= 5;
		game->images.player->instances[0].y -= 5;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->player.y += 5;
		game->images.player->instances[0].y += 5;
	}
//	draw_player(game, game->images.img);
	// mlx_image_to_window(game->mlx, game->img, 0, 0);
}
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
#include <math.h>

void	key_hook(void *param)
{
	t_game *game = param; //change parameters here so we can free our data when ES is pressed


	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.orientation += 0.1;
		if (game->player.orientation > 2 * PI)
			game->player.orientation -= 2 * PI;
		game->player.x_change = cos(game->player.orientation) * game->player.move_speed;
		game->player.y_change = sin(game->player.orientation) * game->player.move_speed;
		draw_rays(game);
		//
//		game->player.x += game->player.x_change;
//		game->player.y += game->player.y_change;
//		game->images.player->instances[0].x += game->player.x_change;
//		game->images.player->instances[0].x += game->player.y_change;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.orientation -= 0.1;
		if (game->player.orientation < 0)
			game->player.orientation += 2 * PI;
		game->player.x_change = cos(game->player.orientation) * game->player.move_speed;
		game->player.y_change = sin(game->player.orientation) * game->player.move_speed;
		draw_rays(game);
//
//		game->player.x += game->player.x_change;
//		game->player.y += game->player.y_change;
//		game->images.player->instances[0].x += game->player.x_change;
//		game->images.player->instances[0].x += game->player.y_change;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->player.x += game->player.x_change;
		game->player.y += game->player.y_change;
		draw_player(game, game->images.img);
//		game->images.player->instances[0].x += (int)game->player.x_change;
//		game->images.player->instances[0].y += (int)game->player.y_change;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->player.x -= game->player.x_change;
		game->player.y -= game->player.y_change;
		draw_player(game, game->images.img);

//		game->images.player->instances[0].x -= (int)game->player.x_change;
//		printf("%f\n", game->player.orientation);
//		game->images.player->instances[0].y -= (int)game->player.y_change;
	}
	printf("%lf\n", game->player.orientation);
	printf("%lf\n", game->player.x_change);
	printf("%lf\n", game->player.y_change);

//	draw_player(game, game->images.img);
	// mlx_image_to_window(game->mlx, game->img, 0, 0);
}
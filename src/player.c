/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:27:39 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/13 13:27:40 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	put_player_to_window(t_game *game)
{
//	game->images.player->instances[0].x = (int)game->player.x;
//	game->images.player->instances[0].y = (int)game->player.y;
}

void draw_player(t_game *game, mlx_image_t *img)
{
//	game->images.player = mlx_new_image(game->mlx, 8, 8);
//	for (int x = 0; x < 8; x++)
//	{
//		for (int y = 0;y < 8; y++)
//		{
//			mlx_put_pixel(game->images.player, x, y, 0xFF0000FF);
//		}
//	}
	for (int x = -5; x < 5; x++)
	{
		for (int y = -5;y < 5; y++)
		{
			mlx_put_pixel(game->images.img, game->player.x + x, game->player.y + y, 0xFF0000FF);
		}
	}
}

void	initialize_player(t_game *game)
{
	game->player.x = 500;
	game->player.y = 500;
	game->player.move_speed = 2.5;
	game->player.orientation = PI;
	game->player.x_change = cos(game->player.orientation) * game->player.move_speed;
	game->player.y_change = sin(game->player.orientation) * game->player.move_speed;
	printf("%lf\n", game->player.orientation);
	printf("%lf\n", game->player.x_change);
	printf("%lf\n", game->player.y_change);
	draw_player(game, game->images.img);
//	mlx_image_to_window(game->mlx, game->images.player, 500, 500);

}

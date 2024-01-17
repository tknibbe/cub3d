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

void	draw_player(t_game *game, mlx_image_t *img, int colour)
{
	double	xSize = WIDTH / game->map_rows;
	double	ySize = HEIGHT / game->map_cols;
//	printf("%lf %lf\n", xSize, ySize);
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
			mlx_put_pixel(game->images.img, game->player.pos.x * xSize + x, game->player.pos.y * ySize + y, colour);
//			printf("this %lf, %d\n", game->player.pos.y, y);
//			printf("%lf, %lf\n", xSize, ySize);
//			printf("that %d %d\n", (int)(game->player.pos.x * xSize + x), (int)(game->player.pos.y * ySize + y));
		}
	}
	for (int x = -2; x < 2; x++)
	{
		for (int y = -2;y < 2; y++)
		{
			mlx_put_pixel(game->images.img, game->player.pos.x * xSize + game->player.dir.x * 20 + x, game->player.pos.y * ySize + game->player.dir.y * 20 + y, colour);

		}
	}

}

void	initialize_player(t_game *game)
{
	game->player.pos.x = 10;
	game->player.pos.y = 3;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.05;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0.66;
//	game->player.x_change = cos(game->player.orientation) * game->player.move_speed;
//	game->player.y_change = sin(game->player.orientation) * game->player.move_speed;
//	printf("%lf\n", game->player.orientation);
//	printf("%lf\n", game->player.x_change);
//	printf("%lf\n", game->player.y_change);
//	draw_player(game, game->images.img, 0xFF0000FF);
//	mlx_image_to_window(game->mlx, game->images.player, 500, 500);

}

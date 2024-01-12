/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:16:25 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/12 17:16:27 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_player(t_game *game, mlx_image_t *img)
{
	game->images.player = mlx_new_image(game->mlx, 10, 10);
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0;y < 10; y++)
		{
			mlx_put_pixel(game->images.player, x, y, 0xFF0000FF);
		}
	}
//	for (int x = -5; x < 5; x++)
//	{
//		for (int y = -5;y < 5; y++)
//		{
//			mlx_put_pixel(img, game->player.x + x, game->player.y + y, 0xFF0000FF);
//		}
//	}
}

void	draw_tile(int x, int y, mlx_image_t *img, int colour, t_game *game)
{
	int	xSize = HEIGHT / game->map_rows;
	int	ySize = WIDTH / game->map_cols;
	int xPos = xSize * x;
	int	yPos = ySize * y;

	// printf("xpos = %d\nyPos = %d\n", xPos,yPos);
	while (xPos < xSize * (x+1))
	{
		while (yPos < ySize * (y+1))
		{
			mlx_put_pixel(img, yPos, xPos, colour);
			yPos++;
		}
		yPos = ySize * y;
		xPos++;
	}
}

mlx_image_t	*test(t_game *game, mlx_t *mlx)
{
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			mlx_put_pixel(img, i, x, 0x808080FF);
		}
	}

	int	x = 0;
	int	y = 0;
	while (game->map[x])
	{
		while (game->map[x][y])
		{
			if (game->map[x][y] == '1' || game->map[x][y] == ' ')
				draw_tile(x, y, img, 0x000000FF, game);
			else
				draw_tile(x, y, img, 0xFFFFFFFF, game);
			y++;
		}
		y = 0;
		x++;
	}
	return (img);
}


void	draw_minimap(t_game *game)
{
	game->images.img  = test(game, game->mlx);
	game->player.x = 500;
	game->player.y = 500;
	draw_player(game, game->images.img);
	mlx_image_to_window(game->mlx, game->images.img, 0, 0);
	mlx_image_to_window(game->mlx, game->images.player, 500, 500);

}

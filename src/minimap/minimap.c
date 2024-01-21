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

// to talk about
// do we increase the HEIGHT and the WIDTH think not
// decide on size of minimap, should probably be square
// decide on tile size, probably 2x2

//void draw_player(t_game *game, mlx_image_t *img)
//{
//	game->images.player = mlx_new_image(game->mlx, 8, 8);
//	for (int x = 0; x < 8; x++)
//	{
//		for (int y = 0;y < 8; y++)
//		{
//			mlx_put_pixel(game->images.player, x, y, 0xFF0000FF);
//		}
//	}
////	for (int x = -5; x < 5; x++)
////	{
////		for (int y = -5;y < 5; y++)
////		{
////			mlx_put_pixel(img, game->player.x + x, game->player.y + y, 0xFF0000FF);
////		}
////	}
//}

void	draw_tile(int y, int x, mlx_image_t *img, int colour, t_game *game)
{
	(void)game;
	int	xSize = CUBE_SIDE;
	int	ySize = CUBE_SIDE;
	int yPos = xSize * y;
	int	xPos = ySize * x;

	// printf("xpos = %d\nyPos = %d\n", xPos,yPos);
	while (yPos < ySize * (y+1))
	{
		while (xPos < xSize * (x+1))
		{
			mlx_put_pixel(img, xPos, yPos, colour);
			xPos++;
		}
		xPos = xSize * x;
		yPos++;
	}
}

double	find_min(double player_pos, int map_dimension)
{
//	double	min_dimension;

//	printf("%lf\n", player_pos);
	if (map_dimension * CUBE_SIDE < MAX_MINIMAP_SIDE)
	{
//		printf("twat\n");

		return (0);
	}
	if (player_pos * CUBE_SIDE > (double)MAX_MINIMAP_SIDE / 2)
	{
		if ((map_dimension - player_pos) * CUBE_SIDE > (double)MAX_MINIMAP_SIDE / 2)
		{
//			printf("this %lf\n", player_pos - (double)MAX_MINIMAP_SIDE / CUBE_SIDE / 2);
			return (player_pos - (double)MAX_MINIMAP_SIDE / CUBE_SIDE / 2);
		}
//		printf("that\n");
		return (player_pos - ((double)MAX_MINIMAP_SIDE / CUBE_SIDE - map_dimension + player_pos));
	}
	return (0);
}

mlx_image_t	*test(t_game *game, mlx_t *mlx, t_minimap *minimap)
{
	(void)minimap;
	mlx_image_t *img = mlx_new_image(mlx, game->minimap.width, game->minimap.height);
	mlx_image_t *test_img = mlx_new_image(mlx, MAX_MINIMAP_SIDE, MAX_MINIMAP_SIDE);
	for (int i = 0; i < game->minimap.width; i++)
	{
		for (int x = 0; x < game->minimap.height; x++)
		{
			mlx_put_pixel(img, i, x, 0x80808088);
		}
	}
	for (int i = 0; i < MAX_MINIMAP_SIDE; i++)
	{
		for (int x = 0; x < MAX_MINIMAP_SIDE; x++)
		{
			mlx_put_pixel(test_img, i, x, 0xFF0000FF);
		}
	}
	int	x = 0;
	int	y = 0;

//	printf("x\n");
	double	start_x = find_min(game->player.pos.x, game->map_cols);
//	printf("y\n");
	double	start_y = find_min(game->player.pos.y, game->map_rows);
	double x_coord;


	printf("map : %d %d\n", game->map_cols, game->map_rows);
	printf("player : %lf %lf\n", game->player.pos.x, game->player.pos.y);
	printf("starts : %lf %lf\n", start_x, start_y);
	while (y < minimap->height)
	{
		x = 0;
		x_coord = start_x;
		while (x < minimap->width)
		{
			if (game->map[(int)start_y][(int)x_coord] == '1')
			{
				mlx_put_pixel(img, x, y, 0x000000AA);
			}
			else if (game->map[(int)start_y][(int )x_coord] == '0')
			{
				mlx_put_pixel(img, x, y, 0xFFFFFFAA);
			}
			x_coord += 0.125;
			x++;
		}
		start_y += 0.125;
		y++;
	}

//	while (game->map[y])
//	{
//		while (game->map[y][x])
//		{
//			if (game->map[y][x] == '1')
//				draw_tile(y, x, img, 0x000000AA, game);
//			else if (game->map[y][x] == '0')
//				draw_tile(y, x, img, 0xFFFFFFAA, game);
//			x++;
//		}
//		x = 0;
//		y++;
//	}
	mlx_image_to_window(game->mlx, test_img, WIDTH - MAX_MINIMAP_SIDE - MARGIN, MARGIN);
	return (img);
}

void	get_minimap_size(t_game *game)
{
	game->minimap.width = game->map_cols * CUBE_SIDE;
	if (game->minimap.width > MAX_MINIMAP_SIDE)
	{
		printf("Width too big");
		game->minimap.width = MAX_MINIMAP_SIDE;
	}
	game->minimap.height = game->map_rows * CUBE_SIDE;
	if (game->minimap.height > MAX_MINIMAP_SIDE)
	{
		printf("Height too big");
		game->minimap.height = MAX_MINIMAP_SIDE;
	}
}

void	draw_minimap(t_game *game)
{
	get_minimap_size(game);
	printf("%d %d\n", game->map_rows, game->map_cols);
	printf("%d %d\n", game->minimap.width, game->minimap.height);
	game->images.minimap  = test(game, game->mlx, &game->minimap);
	mlx_image_to_window(game->mlx, game->images.minimap, WIDTH - game->minimap.width - MARGIN, MARGIN);
//	game->images.img->instances[0].z = 1;
}

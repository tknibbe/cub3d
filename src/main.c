/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:56:28 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/13 17:03:29 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

void	draw_floor_and_ceiling(t_textures text, mlx_image_t *bg) //move to 
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(bg, x, y, text.ceiling);
			else 
				mlx_put_pixel(bg, x, y, text.floor);
			y++;
		}
		y = 0;
		x++;
	}
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

void draw_player(t_game *game, mlx_image_t *img)
{
	for (int x = -5; x < 5; x++)
	{
		for (int y = -5;y < 5; y++)
		{
			mlx_put_pixel(img, game->player.x + x, game->player.y + y, 0xFF0000FF);
		}
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

int	main(int argc, char **argv)
{
	t_game		game;
	// mlx_image_t	*imgnorth;
	// mlx_image_t	*imgeast;
	// mlx_image_t	*imgsouth;
	// mlx_image_t	*imgwest;
	// mlx_image_t	*img;
	// mlx_image_t	*background = NULL;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (get_input(&game, argv[1]))
		return (EXIT_FAILURE);
	game.mlx = mlx_init(WIDTH, HEIGHT, "een goedendag", true);
	game.img  = test(&game, game.mlx);
	// background = mlx_new_image(mlx, WIDTH, HEIGHT);
	// draw_floor_and_ceiling(game.textures, background);
	// imgnorth = mlx_texture_to_image(mlx, game.textures.north);
	// imgeast = mlx_texture_to_image(mlx, game.textures.east);
	// imgsouth = mlx_texture_to_image(mlx, game.textures.south);
	// imgwest = mlx_texture_to_image(mlx, game.textures.west);
	// mlx_image_to_window(mlx, background, 0, 0);
	// mlx_image_to_window(mlx, imgnorth, (WIDTH-200) / 2, 0);
	// mlx_image_to_window(mlx, imgeast,  WIDTH - 200, (HEIGHT -200) / 2);
	// mlx_image_to_window(mlx, imgsouth, (WIDTH-200) / 2, HEIGHT - 200);
	// mlx_image_to_window(mlx, imgwest, 0, (HEIGHT-200)/2);
	game.player.x = 500;
	game.player.y = 500;
	draw_player(&game, game.img);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	//free_shit here
}


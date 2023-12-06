/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:56:28 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/06 14:46:00 by tknibbe          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game		game;
	mlx_image_t	*imgnorth;
	mlx_image_t	*imgeast;
	mlx_image_t	*imgsouth;
	mlx_image_t	*imgwest;
	mlx_image_t	*background = NULL;
	mlx_t		*mlx;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (get_input(&game, argv[1]))
		return (EXIT_FAILURE);
	mlx = mlx_init(WIDTH, HEIGHT, "een goedendag", true);
	background = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_floor_and_ceiling(game.textures, background);
	imgnorth = mlx_texture_to_image(mlx, game.textures.north);
	imgeast = mlx_texture_to_image(mlx, game.textures.east);
	imgsouth = mlx_texture_to_image(mlx, game.textures.south);
	imgwest = mlx_texture_to_image(mlx, game.textures.west);
	mlx_image_to_window(mlx, background, 0, 0);
	mlx_image_to_window(mlx, imgnorth, (WIDTH-200) / 2, 0);
	mlx_image_to_window(mlx, imgeast,  WIDTH - 200, (HEIGHT -200) / 2);
	mlx_image_to_window(mlx, imgsouth, (WIDTH-200) / 2, HEIGHT - 200);
	mlx_image_to_window(mlx, imgwest, 0, (HEIGHT-200)/2);
	mlx_loop_hook(mlx, key_hook, mlx); //only handling escape because i wanted to be able to exit easily
	mlx_loop(mlx);
	//free_shit here
}


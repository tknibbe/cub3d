/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:56:28 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 16:47:23 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"
#include <errno.h>

void	draw_floor_and_ceiling(t_textures text, mlx_image_t *bg) //move to
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(bg, x, y, text.ceiling);
			else
				mlx_put_pixel(bg, x, y, text.floor);
			y++;
		}
		x++;
	}
}

void	set_icon(mlx_t *mlx) // zet jan als icon
{
	mlx_texture_t *pic;

	pic = mlx_load_png("./textures/jan.png");
	if (!pic)
		ft_error_and_exit("Icon location not found\n");
	mlx_set_icon(mlx, pic);
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_memset(&game, 0, sizeof(game)); // weet nog niet of ik dit erin wil houden
	if (get_input(&game, argv[1]))
		return (EXIT_FAILURE);
	initialise_game(&game, argv[1]);
	set_icon(game.mlx);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, fps_counter, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_game_struct(&game);
	return (0);
}


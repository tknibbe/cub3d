/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:56:28 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/14 15:42:58 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_memset(&game, 0, sizeof(game));
	if (get_input(&game, argv[1]))
		return (EXIT_FAILURE);
	initialise_game(&game, argv[1]);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop_hook(game.mlx, fps_counter, &game);
	mlx_loop_hook(game.mlx, check_door, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_game_struct(&game);
	return (0);
}

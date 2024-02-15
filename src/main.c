/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:56:28 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/05 14:43:36 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"

void	print_array(char **arr)
{
	for (int i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
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
//	print_array(game.map);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, fps_counter, &game);
	mlx_loop_hook(game.mlx, check_door, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_game_struct(&game);
	return (0);
}


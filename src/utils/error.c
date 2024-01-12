/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:56:25 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/11 19:56:27 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3d.h"
#include "libft.h"

/**
 * Writes the given string to the standard error and exits
 */
void	ft_error_and_exit(char *error_str)
{
	write(2, error_str, ft_strlen(error_str));
	exit(EXIT_FAILURE);
}

/**
 * Writes an error using mlx error function, stops the mlx instance\n
 * Does not exit nor free things\n
 * Use for mlx functions after the game has bene initialised
 */
//void	ft_mlx_error_after_init(t_game *game)
//{
//	const char	*error_string = mlx_strerror(mlx_errno);
//
//	write(2, error_string, ft_strlen(error_string));
//	write(2, "\n", 1);
//	free_game_struct(game);
//	mlx_close_window(game->mlx);
//	exit(EXIT_FAILURE);
//}

/**
 * Writes an error using mlx error function, frees stuff and exits \n
 * Use for mlx functions
 */
void	ft_mlx_error_and_exit(t_game *game)
{
	const char	*error_string = mlx_strerror(mlx_errno);

	write(2, error_string, ft_strlen(error_string));
	write(2, "\n", 1);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
//		mlx_terminate(game->mlx);
	}
	free_game_struct(game);
	exit(EXIT_FAILURE);
}

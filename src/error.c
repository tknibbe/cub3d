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
 * Writes an error using mlx error function, frees stuff and exits \n
 * Use for mlx functions
 */
void	ft_mlx_error_init(t_game *game)
{
	const char	*error_string = mlx_strerror(mlx_errno);

	write(2, error_string, ft_strlen(error_string));
	write(2, "\n", 1);
	free_game_struct(game);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	exit(EXIT_FAILURE);
}

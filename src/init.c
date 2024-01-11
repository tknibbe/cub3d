/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:22:36 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/11 19:22:38 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	initialise_images(t_game *game)
{
	game->images.fps = mlx_put_string(game->mlx, "FPS 59", 20, 20);
	if (game->images.fps == NULL)
	{
		ft_mlx_error_init(game);
	}
}

void	initialise_game(t_game *game, char *title)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, title, true);
	if (game->mlx == NULL)
	{
		ft_mlx_error_init(game);
	}
	initialise_images(game);
	game->current_time = mlx_get_time();
}

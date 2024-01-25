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

// gets the width and height of the minimap based on the size of the map
// there is a maximum width and height set
// we don't want to go beyond that on big maps
static void	get_minimap_size(t_game *game)
{
	game->minimap.width = game->map_cols * CUBE_SIDE;
	if (game->minimap.width > MAX_MINIMAP_PIXELS)
	{
		game->minimap.width = MAX_MINIMAP_PIXELS;
	}
	game->minimap.height = game->map_rows * CUBE_SIDE;
	if (game->minimap.height > MAX_MINIMAP_PIXELS)
	{
		game->minimap.height = MAX_MINIMAP_PIXELS;
	}
}

void	initialise_minimap(t_game *game, t_minimap *minimap)
{
	get_minimap_size(game);
	game->images.minimap = mlx_new_image(game->mlx, minimap->width, \
													minimap->height);
	minimap->img = game->images.minimap;
	if (minimap->img == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
	draw_minimap(game, minimap);
	if (mlx_image_to_window(game->mlx, minimap->img, \
						WIDTH - minimap->width - MARGIN, \
						MARGIN) == -1)
	{
		ft_mlx_error_and_exit(game);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:41:41 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/23 20:41:42 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// finds the starting coordinate of the minimap in the y or x axis
// depending on the player position on that axis
// we render from coordinate 0 if the whole axis fits within the
// maximum minimap size (we render the whole map from 0 to end in that axis)
// or the player position is within half of the maximum minimap size
//
// if we don't render from 0 that means the player is
// either in the middle of the minimap within
// half of the maximum minimap size on the right side
// that's what the second if statement is for
static double	find_start_coord(double player_pos, int map_axis)
{
	if (map_axis < MAX_MINIMAP_BLOCKS || player_pos <= MAX_MINIMAP_BLOCKS / 2)
	{
		return (0);
	}
	if ((map_axis - player_pos) > MAX_MINIMAP_BLOCKS / 2)
	{
		return (player_pos - MAX_MINIMAP_BLOCKS / 2);
	}
	return (map_axis - MAX_MINIMAP_BLOCKS);
}

static int	colour(char **map, t_vector start, int x, double y_coord)
{
	double	x_coord;

	x_coord = start.x + x * MINIMAP_PIXEL_STEP;
	if (map[(int)y_coord][(int)x_coord] == '1')
	{
		return (0x000000FF);
	}
	else if (map[(int)y_coord][(int)x_coord] == '0')
	{
		return (0xFFFFFFFF);
	}
	else if (map[(int)y_coord][(int)x_coord] == '2')
	{
		return (0xA52A2AFF);
	}
	return (0);
}

static void	draw_tiles(t_minimap *minimap, t_vector start, char **map)
{
	int		x;
	int		y;
	double	y_coord;

	y = 0;
	y_coord = start.y;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			mlx_put_pixel(minimap->img, x, y, colour(map, start, x, y_coord));
			x++;
		}
		y_coord += MINIMAP_PIXEL_STEP;
		y++;
	}
}

void	draw_minimap(t_game *game, t_minimap *minimap)
{
	t_vector	start;

	start.x = find_start_coord(game->player.pos.x, game->map_cols);
	start.y = find_start_coord(game->player.pos.y, game->map_rows);
	draw_tiles(minimap, start, game->map);
	draw_player(game, minimap, start);
}

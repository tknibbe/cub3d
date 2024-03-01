/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:04:34 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/02/14 16:06:38 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// first count the start of the player draw
// player is 4 pixels, 1 pixel is 0.125 in coordinates
// so we want 0.25 on each side of the player, so player start is
// his position minus 0.25
// we then see where we actually want to draw te player on the map
// by substracting from the player the start of the minimap, f.e.
// player pos is x = 2.5, minimap starts at coordinate 0
// player_start = 2.25, and the starting coord is also 2.25
// we then divide by 0.125 to translate coordinates to pixels
static double	get_start_pixel(double axis_pos, double axis_minimap_start)
{
	double	player_start;
	double	start_pixel_coord;

	player_start = axis_pos - 0.25;
	start_pixel_coord = player_start - axis_minimap_start;
	return (start_pixel_coord / MINIMAP_PIXEL_STEP);
}

void	draw_player(t_game *game, t_minimap *minimap, t_vector start)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	start_x = (int)get_start_pixel(game->player.pos.x, start.x);
	start_y = (int)get_start_pixel(game->player.pos.y, start.y);
	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			mlx_put_pixel(minimap->img, start_x + x, start_y + y, 0x0000FFFF);
			x++;
		}
		y++;
	}
}

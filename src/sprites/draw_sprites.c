/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/10 11:58:55 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/10 11:58:55 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define INVIS_COLOUR 0xC929EBFF

// to do
// think about sort stuff. write a new one?
// add David as a sprite
// add comments to stuff so things are more clear
// look at stuff to maybe optimise, in textures as well, add the half heights and stuff
// add maybe to a check for if the player moved so we dont sort or change variables
// refactor files so its more cleaner
// enemies
// make them lose you the game if you walk into them
// add flying and crouching
// otherwise it's just checking if we're on a tyle with an enemy and
// if we're like within 0.25 of the middle of the tile
// how do we make the lose thing, we cna have a you lose thing
// then close the window? I guess we make that
static void	draw_sprite_stripe(t_sprite spr, int tex_x, int x, t_game *game)
{
	int	temp_tex_y;
	int	tex_y;
	int	y;
	int	colour;

	y = spr.draw_start_y;
	temp_tex_y = y - spr.transform_offset - (int)HALF_HEIGHT \
				+ spr.sprite_dimension_half;
	while (y < spr.draw_end_y)
	{
		tex_y = (int)(temp_tex_y * spr.dim_proportion);
		colour = ((int *)spr.tex->pixels)[spr.tex->height * tex_y + tex_x];
		if (colour != (int)INVIS_COLOUR)
			mlx_put_pixel(game->images.maze, x, y, colour);
		y++;
		temp_tex_y++;
	}
}

static void	draw_sprite(t_game *game, t_sprite *spr)
{
	int	x;
	int	tex_x;
	int	temp_tex_x;

	set_sprite_variables(game, spr);
	x = spr->draw_start_x;
	temp_tex_x = x - (spr->sprite_x_on_screen - spr->sprite_dimension_half);
	while (x < spr->draw_end_x)
	{
		tex_x = (int)(temp_tex_x * spr->dim_proportion);
		if (spr->transform_y > 0 && spr->transform_y < game->wall_distances[x])
			draw_sprite_stripe(*spr, tex_x, x, game);
		x++;
		temp_tex_x++;
	}
}

void	draw_sprites(t_game *game)
{
	int	i;

	calc_dist(game->player.pos, game->sprites, game->sprite_nr);
	resort_sprites(game->sprites, game->sprite_nr);
	i = 0;
	while (i < game->sprite_nr)
	{
		draw_sprite(game, &game->sprites[i]);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_variables.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/12 15:16:25 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/12 15:16:25 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	transform_pos_to_camera_plane(t_player plyr, t_sprite *sprt)
{
	double	sprt_x;
	double	sprt_y;
	double	inv;

	sprt_x = sprt->x - plyr.pos.x;
	sprt_y = sprt->y - plyr.pos.y;
	inv = 1.0 / (plyr.plane.x * plyr.dir.y - plyr.dir.x * plyr.plane.y);
	sprt->transform_x = inv * (plyr.dir.y * sprt_x - plyr.dir.x * sprt_y);
	sprt->transform_y = inv * (-plyr.plane.y * sprt_x + plyr.plane.x * sprt_y);
}

static void	calculate_draw_start_and_end(t_sprite *sprite, t_game *game)
{
	int	half_dim;

	half_dim = sprite->sprite_dimension_half;
	sprite->draw_start_x = sprite->sprite_x_on_screen - half_dim;
	sprite->draw_end_x = sprite->sprite_x_on_screen + half_dim;
	sprite->draw_start_y = HALF_HEIGHT - game->wall_off + sprite->transform_offset - half_dim;
	sprite->draw_end_y = HALF_HEIGHT - game->wall_off + sprite->transform_offset + half_dim;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	if (sprite->draw_end_y >= HEIGHT)
		sprite->draw_end_y = HEIGHT - 1;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= WIDTH)
		sprite->draw_end_x = WIDTH - 1;
}

void	set_sprite_variables(t_game *game, t_sprite *spr)
{
	transform_pos_to_camera_plane(game->player, spr);
	spr->sprite_dimension = abs((int)(HEIGHT / spr->transform_y));
	spr->sprite_dimension /= spr->sprite_scale;
	spr->sprite_dimension_half = spr->sprite_dimension / 2;
	spr->dim_proportion = (double)spr->tex->height / spr->sprite_dimension;
	spr->sprite_x_on_screen = (int)(1.0 * HALF_WIDTH * \
								(1 + spr->transform_x / spr->transform_y));
	spr->transform_offset = (int)(spr->height_offset / spr->transform_y);
	calculate_draw_start_and_end(spr, game);
}

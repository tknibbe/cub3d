/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 13:13:00 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/11 13:13:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# define INVIS_COLOUR 0xC929EBFF

# include "cub3d.h"

typedef struct s_game t_game;

typedef struct	s_sprite
{
	double			x;
	double			y;
	double			dist_to_player;
	double			transform_x;
	double			transform_y;
	int				sprite_scale;
	int				sprite_dimension;
	double			dim_proportion;
	int				sprite_dimension_half;
	int				sprite_x_on_screen;
	int				height_offset;
	int				transform_offset;
	int				draw_start_y;
	int				draw_start_x;
	int				draw_end_y;
	int				draw_end_x;
	mlx_texture_t	*tex;
}	t_sprite;

void	add_sprite(t_game *game, t_sprite new_sprite);
void	draw_sprites(t_game *game);
void	sort_sprites(t_sprite *sprites, int sprite_nr);
void	print_sprites(t_sprite *sprites, int sprite_nr); // remove later
void	calc_dist(t_vector player_pos, t_sprite *sprites, int sprite_nr);
void	set_sprite_variables(t_game *game, t_sprite *sprite);
void	resort_sprites(t_sprite *sprites, int sprite_nr);

#endif

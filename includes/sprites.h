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

# include "cub3d.h"

typedef struct s_game t_game;

typedef enum	e_sprt_type
{
	NOTHING = 0,
	CHEERLEADER = 1,
	LAMP = 2,
	GROUND_ENEMY = 4,
	FLYING_ENEMY = 8
}	t_sprt_type;

typedef struct	s_coords
{
	int			x;
	int			y;
	t_sprt_type	type;
}	t_coords;

typedef struct	s_sprite
{
	double			x;
	double			y;
	mlx_texture_t	*tex;
	t_sprt_type		type;
	mlx_texture_t	**tex_cycle;
	int				sprite_scale;
	int				height_offset;
	int				curr_cycle;
	int				tex_nb;
	double			dist_to_player;
	double			transform_x;
	double			transform_y;
	int				sprite_dimension;
	double			dim_proportion;
	int				sprite_dimension_half;
	int				sprite_x_on_screen;
	int				transform_offset;
	int				draw_start_y;
	int				draw_start_x;
	int				draw_end_y;
	int				draw_end_x;
}	t_sprite;

void	draw_sprites(t_game *game);
void	sort_sprites(t_sprite *sprites, int sprite_nr);
void	calc_dist(t_vector player_pos, t_sprite *sprites, int sprite_nr);
void	set_sprite_variables(t_game *game, t_sprite *sprite);
void	resort_sprites(t_sprite *sprites, int sprite_nr);
void	initialise_sprites(t_game *game);
void	initialise_lamps(t_game *game, t_coords *empty_spots, int n);
void	initialise_cheerleaders(t_game *game, t_coords *empty_spots, int n);
void	initialise_enemies(t_game *game);
bool	add_type(t_sprite new_spr, t_game *game, t_coords *empty_spots, int n);
void	randomise_sprites_positions(t_coords *empty_spots, int empty_spots_nr);
void	free_sprite_type(t_sprite sprite);
void	check_for_errors(t_sprite *new_sprite, t_game *game);
bool	is_type_in_array(t_sprite *sprites, int sprite_nr, t_sprt_type type);
void	add_enemies(t_game *game, t_sprite ground_enemy, t_sprite flying_enemy);
void	load_textures(char *path, t_sprite *new_sprite);
int		identify_enemy(t_game *game, int x, int y);

#endif

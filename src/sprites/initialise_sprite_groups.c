/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_sprite_groups.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 16:41:09 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/19 16:41:09 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite	initialise_flying_enemy(t_game *game)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 3;
	new_sprite.type = FLYING_ENEMY;
	new_sprite.curr_cycle = 0;
	load_textures("textures/enemy_flying/", &new_sprite);
	check_for_errors(&new_sprite, game);
	*new_sprite.tex = *new_sprite.tex_cycle[0];
	new_sprite.height_offset = -1 * (int)new_sprite.tex->height;
	return (new_sprite);
}

static t_sprite	initialise_ground_enemy(t_game *game)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 3;
	new_sprite.type = GROUND_ENEMY;
	new_sprite.curr_cycle = 0;
	load_textures("textures/enemy_ground/", &new_sprite);
	check_for_errors(&new_sprite, game);
	*new_sprite.tex = *new_sprite.tex_cycle[0];
	new_sprite.height_offset = (int)new_sprite.tex->height;
	return (new_sprite);
}

// initialises enemies, a lot of variables are the same between sprites
// only thing that differs is the coordinates of the sprite
// the sprites share the pointers to the textures,
// so we only allocate once per sprite type
// they also contain z tex variable that hold the value
// of the texture currently displayed
// (changes every couple frames for animation)
// scale decides how big the sprite is
// height offset sets how high the sprite is on the screen
// enemies are on the ground
void	initialise_enemies(t_game *game)
{
	t_sprite		ground_enemy;
	t_sprite		flying_enemy;

	ground_enemy = initialise_ground_enemy(game);
	flying_enemy = initialise_flying_enemy(game);
	add_enemies(game, ground_enemy, flying_enemy);
	if (is_type_in_array(game->sprites, game->sprite_nr, GROUND_ENEMY) == false)
		free_sprite_type(ground_enemy);
	if (is_type_in_array(game->sprites, game->sprite_nr, FLYING_ENEMY) == false)
		free_sprite_type(flying_enemy);
}

// initialises cheerleaders, a lot of variables are the same between sprites
// only thing that differs is the coordinates of the sprite
// the sprites share the pointers to the textures,
// so we only allocate once per sprite type
// they also contain z tex variable that hold the value
// of the texture currently displayed
// (changes every couple frames for animation)
// scale decides how big the sprite is
// height offset sets how high the sprite is on the screen
// cheerleaders are on the ground
void	initialise_cheerleaders(t_game *game, t_coords *empty_spots, int n)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 3;
	new_sprite.type = CHEERLEADER;
	new_sprite.curr_cycle = 0;
	load_textures("textures/cheerleader/", &new_sprite);
	check_for_errors(&new_sprite, game);
	*new_sprite.tex = *new_sprite.tex_cycle[0];
	new_sprite.height_offset = (int)new_sprite.tex->height;
	if (add_type(new_sprite, game, empty_spots, n) == false)
		free_sprite_type(new_sprite);
}

// initialises lamps, a lot of variables are the same between sprites
// only thing that differs is the coordinates of the sprite
// the sprites share the pointers to the textures,
// so we only allocate once per sprite type
// they also contain a tex variable that hold the value
// of the texture currently displayed
// (changes every couple frames for animation)
// scale decides how big the sprite is
// height offset sets how high the sprite is on the screen
// lamps are on the ceiling
void	initialise_lamps(t_game *game, t_coords *empty_spots, int n)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 4;
	new_sprite.type = LAMP;
	new_sprite.curr_cycle = 0;
	load_textures("textures/lamp/", &new_sprite);
	check_for_errors(&new_sprite, game);
	*new_sprite.tex = *new_sprite.tex_cycle[0];
	new_sprite.height_offset = -1 * (int)new_sprite.tex->height;
	if (add_type(new_sprite, game, empty_spots, n) == false)
		free_sprite_type(new_sprite);
}

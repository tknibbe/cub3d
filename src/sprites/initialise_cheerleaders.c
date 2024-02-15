/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_cheerleaders.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/15 11:59:16 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/15 11:59:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_textures(t_sprite *new_sprite, t_game *game)
{
	new_sprite->tex_cycle[0] = mlx_load_png("textures/tymon_sprite_teeth.png");
	new_sprite->tex_cycle[1] = mlx_load_png("textures/tymon_sprite.png");
	check_for_errors(new_sprite, game);
	*new_sprite->tex = *new_sprite->tex_cycle[0];
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
	new_sprite.tex_nb = 2;
	new_sprite.type = LAMP;
	new_sprite.curr_cycle = 0;
	new_sprite.tex_cycle = malloc(sizeof(mlx_texture_t *) * new_sprite.tex_nb);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	if (new_sprite.tex_cycle == NULL || new_sprite.tex == NULL)
		ft_error_and_exit("Malloc failure\n");
	load_textures(&new_sprite, game);
	new_sprite.height_offset = (int)new_sprite.tex->height;
	add_type(new_sprite, game, empty_spots, n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_sprites.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 15:25:31 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/14 15:25:31 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialise_sprites(t_game *game)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 2;
	new_sprite.texture_nbr = 2;
	new_sprite.type = LAMP;
	new_sprite.texture_cycle = malloc(8 * 2);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	new_sprite.curr_cycle = 0;
	new_sprite.x = 7.5;
	new_sprite.y = 7.5;
	new_sprite.texture_cycle[0] = mlx_load_png("textures/tymon_sprite_teeth.png");
	new_sprite.texture_cycle[1] = mlx_load_png("textures/tymon_sprite.png");
//	new_sprite.texture_cycle[2] = mlx_load_png("textures/tymon.png");
	*new_sprite.tex = *new_sprite.texture_cycle[0];

	new_sprite.height_offset = -new_sprite.tex->height;
	add_sprite(game, new_sprite);
	new_sprite.x = 8.5;
	new_sprite.y = 7.5;
	add_sprite(game, new_sprite);
	new_sprite.x = 9.5;
	new_sprite.y = 7.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 10.5;
	new_sprite.y = 7.5;
	new_sprite.type = CHEERLEADER;
	new_sprite.texture_cycle = malloc(8 * 3);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	new_sprite.texture_cycle[0] = mlx_load_png("textures/tymon_sprite_teeth.png");
	new_sprite.texture_cycle[1] = mlx_load_png("textures/tymon_sprite.png");
//	new_sprite.texture_cycle[2] = mlx_load_png("textures/tymon.png");
	*new_sprite.tex = *new_sprite.texture_cycle[0];
	new_sprite.height_offset = new_sprite.tex->height;
	new_sprite.curr_cycle = 1;


	add_sprite(game, new_sprite);
	new_sprite.x = 11.5;
	new_sprite.y = 7.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 7.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 7.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 8.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 9.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 10.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 11.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 12.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 11.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 1.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 10.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
}


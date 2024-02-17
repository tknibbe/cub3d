/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_enemies.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 11:11:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/16 11:11:23 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>
//
//static void	set_type(t_sprite *new_sprite, mlx_texture_t **enemy_textures)
//{
//	if (rand() % 2 == 0)
//	{
//		new_sprite->type = GROUND_ENEMY;
//		new_sprite->height_offset = (int)new_sprite->tex->height;
//		new_sprite->tex_cycle[0] = enemy_textures[0];
//		new_sprite->tex_cycle[1] = enemy_textures[1];
//		*new_sprite->tex = *new_sprite->tex_cycle[0];
//	}
//	else
//	{
//		new_sprite->type = FLYING_ENEMY;
//		new_sprite->height_offset = -1 * (int)new_sprite->tex->height;
//		new_sprite->tex_cycle[0] = enemy_textures[2];
//		new_sprite->tex_cycle[1] = enemy_textures[3];
//		*new_sprite->tex = *new_sprite->tex_cycle[0];
//	}
//}

t_sprite	choose_type(t_sprite new_sprite_ground, t_sprite new_sprite_flying)
{
	if (rand() % 2 == 0)
		return (new_sprite_ground);
	else
		return (new_sprite_flying);
}

static void	add_enemies(t_game *game, t_sprite new_sprite_ground, t_sprite new_sprite_flying)
{
	int			y;
	int			x;
	t_sprite	new_sprite;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == '4')
			{
				new_sprite = choose_type(new_sprite_ground, new_sprite_flying);
				new_sprite.y = y + 0.5;
				new_sprite.x = x + 0.5;
				add_sprite(game, new_sprite);
				printf("lol\n");
			}
			x++;
		}
		y++;
	}
}
//
//static void	load_textures_ground(mlx_texture_t	**tex_cycle, t_game *game, int n)
//{
//	enemy_textures[0] = mlx_load_png("textures/tymon.png");
//	enemy_textures[1] = mlx_load_png("textures/roodmuurtje.png");
//	enemy_textures[2] = mlx_load_png("textures/tymon.png");
//	enemy_textures[3] = mlx_load_png("textures/roodmuurtje.png");
//	check_for_errors(enemy_textures, game, n);
////	*enemy_textures->tex = *enemy_textures->tex_cycle[0];
//}

static void	load_textures_ground(t_sprite *new_sprite, t_game *game)
{
	new_sprite->tex_cycle[0] = mlx_load_png("textures/tymon.png");
	new_sprite->tex_cycle[1] = mlx_load_png("textures/roodmuurtje.png");
	check_for_errors(new_sprite->tex_cycle, game, new_sprite->tex_nb);
	*new_sprite->tex = *new_sprite->tex_cycle[0];
}


static void	load_textures_flying(t_sprite *new_sprite, t_game *game)
{
	new_sprite->tex_cycle[0] = mlx_load_png("textures/tymon.png");
	new_sprite->tex_cycle[1] = mlx_load_png("textures/geelmuurtje.png");
	check_for_errors(new_sprite->tex_cycle, game,new_sprite->tex_nb);
	*new_sprite->tex = *new_sprite->tex_cycle[0];
}


t_sprite	initialise_flying_enemy(t_game *game)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 3;
	new_sprite.tex_nb = 2;
	new_sprite.type = FLYING_ENEMY;
	new_sprite.curr_cycle = 0;
	new_sprite.tex_cycle = malloc(sizeof(mlx_texture_t *) * new_sprite.tex_nb);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	if (new_sprite.tex_cycle == NULL || new_sprite.tex == NULL)
		ft_error_and_exit("Malloc failure\n");
	load_textures_flying(&new_sprite, game);
	new_sprite.height_offset = -1 * (int)new_sprite.tex->height;
	return (new_sprite);
}


t_sprite	initialise_ground_enemy(t_game *game)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 3;
	new_sprite.tex_nb = 2;
	new_sprite.type = GROUND_ENEMY;
	new_sprite.curr_cycle = 0;
	new_sprite.tex_cycle = malloc(sizeof(mlx_texture_t *) * new_sprite.tex_nb);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	if (new_sprite.tex_cycle == NULL || new_sprite.tex == NULL)
		ft_error_and_exit("Malloc failure\n");
	load_textures_ground(&new_sprite, game);
	new_sprite.height_offset = (int)new_sprite.tex->height;
	return (new_sprite);
}

bool	is_type_in_array(t_sprite *sprites, int sprite_nr, t_sprt_type type)
{
	int		i;

	i = 0;
	while (i < sprite_nr)
	{
		if (sprites[i].type == type)
			return (true);
		i++;
	}
	return (false);
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
	t_sprite		new_sprite_ground;
	t_sprite		new_sprite_flying;

	new_sprite_ground = initialise_ground_enemy(game);
	new_sprite_flying = initialise_flying_enemy(game);
	add_enemies(game, new_sprite_ground, new_sprite_flying);
	if (is_type_in_array(game->sprites, game->sprite_nr, GROUND_ENEMY) == false)
		free_sprite_type(new_sprite_ground);
	if (is_type_in_array(game->sprites, game->sprite_nr, FLYING_ENEMY) == false)
		free_sprite_type(new_sprite_flying);
}

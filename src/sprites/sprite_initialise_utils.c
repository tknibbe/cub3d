/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_initialise_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/17 16:04:31 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/17 16:04:31 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	check_for_errors(t_sprite *new_sprite, t_game *game)
{
	int	i;

	i = 0;
	while (i < new_sprite->tex_nb)
	{
		if (new_sprite->tex_cycle[i] == NULL)
			ft_mlx_error_and_exit(game);
		i++;
	}
}

static void	add_sprite(t_game *game, t_sprite new_sprite)
{
	int			i;
	t_sprite	*new_sprites;

	new_sprites = ft_calloc(game->sprite_nr + 1, sizeof(t_sprite));
	if (new_sprites == NULL)
		ft_error_and_exit("Malloc failure\n");
	i = 0;
	while (i < game->sprite_nr)
	{
		new_sprites[i] = game->sprites[i];
		i++;
	}
	new_sprites[i] = new_sprite;
	game->sprite_nr++;
	free(game->sprites);
	game->sprites = new_sprites;
}

// loops through empty spots and checks if the sprite type
// in the empty spot corresponds to the current sprite
// if it does we add the sprite to the array with the
// coordinates of the empty spot
bool	add_type(t_sprite new_spr, t_game *game, t_coords *empty_spots, int n)
{
	int		i;
	bool	was_added;

	i = 0;
	was_added = false;
	while (i < n)
	{
		if (new_spr.type == empty_spots[i].type)
		{
			new_spr.x = empty_spots[i].x + 0.5;
			new_spr.y = empty_spots[i].y + 0.5;
			add_sprite(game, new_spr);
			was_added = true;
		}
		i++;
	}
	return (was_added);
}

static t_sprite	choose_type(t_sprite ground_enemy, t_sprite flying_enemy)
{
	if (rand() % 2 == 0)
		return (ground_enemy);
	else
		return (flying_enemy);
}

void	add_enemies(t_game *game, t_sprite ground_enemy, t_sprite flying_enemy)
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
				new_sprite = choose_type(ground_enemy, flying_enemy);
				new_sprite.y = y + 0.5;
				new_sprite.x = x + 0.5;
				add_sprite(game, new_sprite);
			}
			x++;
		}
		y++;
	}
}

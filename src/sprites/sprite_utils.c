/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 15:21:32 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/11 15:21:32 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	print_sprites(t_sprite *sprites, int sprite_nr)
{
	int	i;

	i = 0;
	while (i < sprite_nr)
	{
		printf("%lf %lf %lf\n", sprites[i].x, sprites[i].y, sprites[i].dist_to_player);
		i++;
	}
	printf("\n");
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

void	calc_dist(t_vector player_pos, t_sprite *sprites, int sprite_nr)
{
	int		i;
	double	x_sq;
	double	y_sq;

	i = 0;
	while (i < sprite_nr)
	{
		x_sq = (player_pos.x - sprites[i].x) * (player_pos.x - sprites[i].x);
		y_sq = (player_pos.y - sprites[i].y) * (player_pos.y - sprites[i].y);
		sprites[i].dist_to_player = x_sq + y_sq;
		i++;
	}
}

void	resort_sprites(t_sprite *sprites, int sprite_nr)
{
	int			j;
	t_sprite	temp;

	j = 0;
	while (j < sprite_nr - 1)
	{
		if (sprites[j].dist_to_player < sprites[j + 1].dist_to_player)
		{
			temp = sprites[j];
			sprites[j] = sprites[j + 1];
			sprites[j + 1] = temp;
		}
		j++;
	}
}

void	sort_sprites(t_sprite *sprites, int sprite_nr)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < sprite_nr - 1)
	{
		j = 0;
		while (j < sprite_nr - i - 1)
		{
			if (sprites[j].dist_to_player < sprites[j + 1].dist_to_player)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	add_sprite(t_game *game, t_sprite new_sprite)
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

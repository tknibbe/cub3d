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

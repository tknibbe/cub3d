/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fix_textures.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 12:16:00 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/08 12:16:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap_values(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint8_t	temp;

	temp = texture->pixels[(texture->height * y + x) * 4];
	texture->pixels[(texture->height * y + x) * 4] = texture->pixels[(texture->height * y + x) * 4 + 3];
	texture->pixels[(texture->height * y + x) * 4 + 3] = temp;
	temp = texture->pixels[(texture->height * y + x) * 4 + 1];
	texture->pixels[(texture->height * y + x) * 4 + 1] = texture->pixels[(texture->height * y + x) * 4 + 2];
	texture->pixels[(texture->height * y + x) * 4 + 2] = temp;
}

static void	fix_texture(mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			swap_values(texture, x, y);
			x++;
		}
		y++;
	}
}

static void fix_sprite_type(t_sprite sprite)
{
	int	i;

	i = 0;
	while (i < sprite.texture_nbr)
	{
		fix_texture(sprite.texture_cycle[i]);
		i++;
	}
}

static void	fix_sprite_textures(t_sprite *sprites, int sprite_nr)
{
	int				i;
	unsigned int	already_done;

	i = 0;
	already_done = 0;
	while (i < sprite_nr)
	{
		if ((sprites[i].type & already_done) == 0)
		{
			fix_sprite_type(sprites[i]);
			already_done |= sprites[i].type;
		}
		i++;
	}
}

void	fix_textures(t_game *game)
{
	fix_texture(game->textures.east);
	fix_texture(game->textures.north);
	fix_texture(game->textures.south);
	fix_texture(game->textures.west);
	fix_texture(game->textures.door);
	fix_sprite_textures(game->sprites, game->sprite_nr);
}

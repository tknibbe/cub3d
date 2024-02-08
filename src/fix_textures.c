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

void	fix_textures(t_game *game)
{
	fix_texture(game->textures.east);
	fix_texture(game->textures.north);
	fix_texture(game->textures.south);
	fix_texture(game->textures.west);
}

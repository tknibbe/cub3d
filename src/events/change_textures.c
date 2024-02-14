/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 14:04:12 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/14 14:04:12 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	change_sprite_textures(t_sprite *sprites, int sprite_nr)
{
	int				i;
	unsigned int	already_done;

	i = 0;
	already_done = 0;
	while (i < sprite_nr)
	{
		if ((sprites[i].type & already_done) == 0)
		{
			sprites[i].curr_cycle = (sprites[i].curr_cycle + 1) % sprites[i].texture_nbr;
			*(sprites[i].tex) = *sprites[i].texture_cycle[sprites[i].curr_cycle];
			already_done |= sprites[i].type;
		}
		i++;
	}
}

static void	adjust_texture(mlx_texture_t *tex)
{
	uint8_t	*row;

	row = malloc(tex->width * 5 * 4);
	if (row == NULL)
		ft_error_and_exit("Malloc failure\n");
	ft_memmove(row, tex->pixels, tex->width * 5 * 4);
	ft_memmove(tex->pixels, tex->pixels + tex->width * 5 * 4, tex->width * tex->height * 4 - tex->width * 5 * 4);
	ft_memmove(tex->pixels + tex->width * tex->height * 4 - tex->width * 5 * 4, row, tex->width * 5 * 4);
	free(row);
}

void	adjust_textures(t_game *game)
{
	adjust_texture(game->textures.north);
	adjust_texture(game->textures.east);
	adjust_texture(game->textures.south);
	adjust_texture(game->textures.west);
	change_sprite_textures(game->sprites, game->sprite_nr);
}


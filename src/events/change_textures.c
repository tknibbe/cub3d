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

static void	change_sprite_textures(t_sprite *sprt, int sprite_nr)
{
	int				i;
	unsigned int	already_done;

	i = 0;
	already_done = 0;
	while (i < sprite_nr)
	{
		if ((sprt[i].type & already_done) == 0)
		{
			sprt[i].curr_cycle = (sprt[i].curr_cycle + 1) % sprt[i].tex_nb;
			*(sprt[i].tex) = *sprt[i].tex_cycle[sprt[i].curr_cycle];
			already_done |= sprt[i].type;
		}
		i++;
	}
}

static void	adjust_texture(mlx_texture_t *tex)
{
	uint8_t		*row;
	long int	moved_bytes;

	moved_bytes = tex->width * 5 * 4;
	row = malloc(moved_bytes);
	if (row == NULL)
		ft_error_and_exit("Malloc failure\n");
	ft_memmove(row, tex->pixels, moved_bytes);
	ft_memmove(tex->pixels, tex->pixels + moved_bytes, \
			tex->width * tex->height * 4 - moved_bytes);
	ft_memmove(tex->pixels + tex->width * tex->height * 4 - moved_bytes, \
		row, moved_bytes);
	free(row);
}

static void	adjust_textures(t_game *game)
{
	adjust_texture(game->textures.north);
	adjust_texture(game->textures.east);
	adjust_texture(game->textures.south);
	adjust_texture(game->textures.west);
	change_sprite_textures(game->sprites, game->sprite_nr);
}

void	change_textures(t_game *game)
{
	static double	time;

	if (mlx_get_time() - time > 0.08)
	{
		time = mlx_get_time();
		adjust_textures(game);
		ray_caster(game);
		draw_sprites(game);
	}
}

//void	change_textures(t_game *game)
//{
//	static int frame;
//
//	frame++;
//	if (frame == 5)
//	{
//		frame = 0;
//		adjust_textures(game);
//		ray_caster(game);
//		draw_sprites(game);
//	}
//}

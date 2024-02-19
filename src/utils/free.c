/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:26:40 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/02/15 17:23:16 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

//these might not be neccesary

//static void	safe_delete_image(t_game *game, mlx_image_t	*image)
//{
//	if (game->mlx && image)
//		mlx_delete_image(game->mlx, image);
//}
//
//static void	free_images(t_game *game, t_images images)
//{
//	safe_delete_image(game, images.fps);
//	safe_delete_image(game, images.img);
//}

static void	safe_delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	free_sprite_type(t_sprite sprite)
{
	int	i;

	i = 0;
	while (i < sprite.tex_nb)
	{
		safe_delete_texture(sprite.tex_cycle[i]);
		i++;
	}
	free(sprite.tex_cycle);
	free(sprite.tex);
}

static void	free_sprites(t_sprite *sprites, int sprite_nr)
{
	int				i;
	unsigned int	already_done;

	i = 0;
	already_done = 0;
	while (i < sprite_nr)
	{
		if ((sprites[i].type & already_done) == 0)
		{
			free_sprite_type(sprites[i]);
			already_done |= sprites[i].type;
		}
		i++;
	}
	free(sprites);
}

static void	free_textures(t_textures textures)
{
	safe_delete_texture(textures.north);
	safe_delete_texture(textures.east);
	safe_delete_texture(textures.south);
	safe_delete_texture(textures.west);
	safe_delete_texture(textures.door);
	safe_delete_texture(textures.icon);
}

/**
 * Frees everything in the struct, assumes everything is NULL or malloced
 */
void	free_game_struct(t_game *game)
{
//	free_images(game, game->images);
	free_textures(game->textures);
	free_sprites(game->sprites, game->sprite_nr);
	ft_free_array(game->map);
	free(game->wall_distances);
	free(game->img_buffer);
}

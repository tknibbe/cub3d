/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:26:40 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/25 19:46:29 by tknibbe          ###   ########.fr       */
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

static void	free_textures(t_textures textures, t_game *game)
{
	int	i;

	safe_delete_texture(textures.north);
	safe_delete_texture(textures.east);
	safe_delete_texture(textures.south);
	safe_delete_texture(textures.west);
	safe_delete_texture(textures.door);
	safe_delete_texture(textures.icon);
	i = 0;
	while (i < game->sprite_nr)
	{
		safe_delete_texture(game->sprites[i].tex);
		i++;
	}
}

/**
 * Frees everything in the struct, assumes everything is NULL or malloced
 */
void	free_game_struct(t_game *game)
{
//	free_images(game, game->images);
	free_textures(game->textures, game);
	ft_free_array(game->map);
	free(game->sprites);
	free(game->wall_distances);
}

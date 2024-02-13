/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:46:29 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/05 14:53:17 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	fov_change(t_player *player, t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_MINUS) && player->fov > 50)
	{
		player->plane.x *= 0.95;
		player->plane.y *= 0.95;
		player->fov = fov(player->plane.x, player->plane.y);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_EQUAL) && player->fov < 100)
	{
		player->plane.x *= 1.05;
		player->plane.y *= 1.05;
		player->fov = fov(player->plane.x, player->plane.y);
	}
}

void	adjust_texture(mlx_texture_t *tex)
{
	uint8_t *row;

	row = malloc(tex->width * 5 * 4);
	if (row == NULL)
		ft_error_and_exit("Malloc failure\n");
	ft_memmove(row, tex->pixels, tex->width * 5 * 4);
	ft_memmove(tex->pixels, tex->pixels + tex->width * 5 * 4, tex->width * tex->height * 4 - tex->width * 5 * 4);
	ft_memmove(tex->pixels + tex->width * tex->height * 4 - tex->width * 5 * 4, row, tex->width * 5 * 4);
	free(row);
}

void	change_sprites(t_sprite *sprites, int sprite_nr)
{
	int	i;
	unsigned int alread_done;

	i = 0;
	alread_done = 0;
	while (i < sprite_nr)
	{
		if ((sprites[i].type & alread_done) == 0)
		{
//			printf("%dspr\n", sprites[i].curr_cycle);
			sprites[i].curr_cycle = (sprites[i].curr_cycle + 1) % 2;
			printf("%dspr\n", sprites[i].curr_cycle);
			*(sprites[i].tex) = *sprites[i].texture_cycle[sprites[i].curr_cycle];
			alread_done |= sprites[i].type;
		}
		i++;
	}
	printf("done\n\n");
}

void	key_hook(void *param)
{
	t_game	*game;
	static int	frame;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	movement(&game->player, game);
	fov_change(&game->player, game);
	if (game->player.has_moved == true)
	{
		ray_caster(game);
		game->player.has_moved = false;
		draw_sprites(game);
	}
	frame++;
	if (frame == 5)
	{
		frame = 0;
		adjust_texture(game->textures.north);
		adjust_texture(game->textures.east);
		adjust_texture(game->textures.south);
		adjust_texture(game->textures.west);
		ray_caster(game);
		change_sprites(game->sprites, game->sprite_nr);
		draw_sprites(game);
	}
	open_door(game);
}

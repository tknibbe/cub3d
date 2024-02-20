/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:46:29 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/15 15:18:34 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <unistd.h>

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

void	loop_hook(void *param)
{
	t_game *game;
	static int frame;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	movement(&game->player, game);
	fov_change(&game->player, game);
	if (check_death(game) == true)
		return ;
	if (game->player.has_moved == true)
	{
		ray_caster(game);
		game->player.has_moved = false;
		draw_sprites(game);
	}
	frame++;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL))
	{
		game->wall_off = 300;
//		game->wall_off += 5;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
	{

		game->wall_off = -300;
//		game->wall_off -= 5;
	}
//	printf("%d\n", game->wall_off);
	else
		game->wall_off = 0;
	if (frame == 5)
	{
		frame = 0;
		adjust_textures(game);
		ray_caster(game);
		draw_sprites(game);
	}
	check_door(game);
}

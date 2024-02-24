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

static void	flying_crouch(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
	{
		game->camera_height = 300;
		game->player.state = FLYING;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL))
	{
		game->camera_height = -300;
		game->player.state = CROUCHING;
	}
	else
	{
		game->camera_height = 0;
		game->player.state = NORMAL;
	}
}

void	loop_hook(void *param)
{
	t_game		*game;

	game = param;
	if (check_death(game) == true)
		return ;
	movement(&game->player, game);
	flying_crouch(game);
	fov_change(&game->player, game);
	check_door(game);
	if (game->player.has_moved == true)
	{
		ray_caster(game);
		draw_sprites(game);
		game->player.has_moved = false;
	}
	change_textures(game);
}

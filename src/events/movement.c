/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:19:37 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/14 20:19:38 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static t_vector	get_sign(t_vector dir, int direction)
{
	t_vector	sign;

	if (dir.x > 0)
		sign.x = direction;
	else
		sign.x = -direction;
	if (dir.y > 0)
		sign.y = direction;
	else
		sign.y = -direction;
	return (sign);
}

static void	move(t_player *player, t_vector dir,int direction, char **grid)
{
	t_vector	new_pos;
	t_vector		sign;

	new_pos.x = player->pos.x + dir.x * player->move_speed * direction;
	new_pos.y = player->pos.y + dir.y * player->move_speed * direction;
	sign = get_sign(dir, direction);
	if (grid[(int)player->pos.y][(int)(new_pos.x + 0.3 * sign.x)] == '0')
		player->pos.x = new_pos.x;
	if (grid[(int)(new_pos.y + 0.3 * sign.y)][(int)player->pos.x] == '0')
		player->pos.y = new_pos.y;
}

static void	strafe(t_player *player, int direction, char **map)
{
	double		cosinus;
	double		sinus;
	t_vector	new_dir;
	double	dir_x;
	double	dir_y;

	cosinus = cos(0.5 * PI);
	sinus = sin(0.5 * PI);
	new_dir.x = player->dir.x * cosinus - player->dir.y * sinus;
	new_dir.y = player->dir.x * sinus + player->dir.y * cosinus;
	move(player, new_dir, direction, map);
}

static void	rotate(t_player *player, int rotation)
{
	double	sinus;
	double	cosinus;
	double	old_x;
	double	old_plane_x;

	cosinus = cos(player->rot_speed * rotation);
	sinus = sin(player->rot_speed * rotation);
	old_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cosinus - player->dir.y * sinus;
	player->dir.y = old_x * sinus + player->dir.y * cosinus;
	player->plane.x = player->plane.x * cosinus - player->plane.y * sinus;
	player->plane.y = old_plane_x * sinus + player->plane.y * cosinus;
}

void	movement(t_player *player, t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(player, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(player, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		strafe(player, -1, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		strafe(player, 1, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) \
		|| mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		move(player, player->dir, -1, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) \
		|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
		move(player, player->dir, 1, game->map);
}

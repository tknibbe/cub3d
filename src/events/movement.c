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

static void	move(t_player *player, int direction, char **grid)
{
	double	delta_x;
	double	delta_y;

	delta_x = player->dir.x * player->move_speed * direction;
	delta_y = player->dir.y * player->move_speed * direction;
//	grid[player->pos.x + delta_x][player->pos.y]
//	printf("position: %lf, %lf\n", player->pos.y, player->pos.x);
//	printf("deltas: %lf, %lf\n", delta_y, delta_x);
//	printf("actual grid%c\n", grid[3][7]);
//	printf("%c\n", grid[(int)player->pos.y][(int)(player->pos.x + 0.1 * direction)]);
//
//	printf("importanto %d direction %d\n", (int)(player->pos.x + 0.1 * direction), direction);
//	printf("DIRECTION: %d\n", direction);
	if (grid[(int)player->pos.y][(int)(player->pos.x + delta_x)] == '0')
		player->pos.x += player->dir.x * player->move_speed * direction;
	if (grid[(int)(player->pos.y + delta_y)][(int)player->pos.x] == '0')
		player->pos.y += player->dir.y * player->move_speed * direction;
}

static void	strafe(t_player *player, int direction, char **map)
{
	double	cosinus;
	double	sinus;
	double	dir_x;
	double	dir_y;

	cosinus = cos(0.5 * PI);
	sinus = sin(0.5 * PI);
	dir_x = player->dir.x * cosinus - player->dir.y * sinus;
	dir_y = player->dir.x * sinus + player->dir.y * cosinus;
	player->pos.x += dir_x * player->move_speed * direction;
	player->pos.y += dir_y * player->move_speed * direction;
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
		move(player, -1, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) \
		|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
		move(player, 1, game->map);
}

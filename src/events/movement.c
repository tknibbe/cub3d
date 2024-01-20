/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:19:37 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/18 15:25:51 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// this function checks what direction we're moving into based on the
// direction vector and the key we pressed (indicated by direction) then
// it returns the actual direction we're moving into to our previous function
// this is for checking collisions and
// keeping a 0.3 distance between the player and wall
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

// direction integer tells us which way we're moving, 1 is forward
// -1 is backwards
// the dir vector is the direction vector the player is facing it
// contains how much we move in the x direction and how much in the y direction
static void	move(t_player *player, t_vector dir, int direction, char **grid)
{
	t_vector	new_pos;
	t_vector	sign;

	new_pos.x = player->pos.x + dir.x * player->move_speed * direction;
	new_pos.y = player->pos.y + dir.y * player->move_speed * direction;
	sign = get_sign(dir, direction);
	if (grid[(int)player->pos.y][(int)(new_pos.x + 0.3 * sign.x)] == '0')
		player->pos.x = new_pos.x;
	if (grid[(int)(new_pos.y + 0.3 * sign.y)][(int)player->pos.x] == '0')
		player->pos.y = new_pos.y;
}

// for moving left and right we need to rotate our direction vector
// by 90 degrees, which is 0.5 PI
static void	strafe(t_player *player, int direction, char **map)
{
	double		cosinus;
	double		sinus;
	t_vector	new_dir;

	cosinus = cos(0.5 * PI);
	sinus = sin(0.5 * PI);
	new_dir.x = player->dir.x * cosinus - player->dir.y * sinus;
	new_dir.y = player->dir.x * sinus + player->dir.y * cosinus;
	move(player, new_dir, direction, map);
}

// rotation rotates both the plane of the camera and the direction vector
// the player is facing, the rotation integer is to decide which
// side we are rotating, if its positive we rotate left
// if it's negative we rotate right
void	rotate(t_player *player, int rotation)
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

void	pitagoras(double a, double b)
{
	double	len;

	len = a * a + b * b;
//	printf("%lf\n", sqrt(len));
	double lol = 2 * atan(sqrt(len));
	printf("%lf\n", lol * 180 / PI);
}

void	movement(t_player *player, t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(player, -2);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(player, 2);
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		game->player.move_speed = 0.15;
	if (!mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		game->player.move_speed = 0.05;
//	printf("%lf %lf\n", game->player.plane.x, game->player.plane.y);
//	pitagoras(game->player.dir.x, game->player.dir.y);
//	pitagoras(game->player.plane.x, game->player.plane.y);
}

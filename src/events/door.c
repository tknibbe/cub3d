/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:22:31 by tymonknibbe       #+#    #+#             */
/*   Updated: 2024/02/08 12:53:38 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	door_is_near(char **map, t_vector pos)
{
	int	new_x;
	int	new_y;

	new_x = (int) pos.x;
	new_y = (int) pos.y;
	if (map[new_y - 1][new_x] == '2' ||
		map[new_y + 1][new_x] == '2' ||
		map[new_y][new_x - 1] == '2' ||
		map[new_y][new_x + 1] == '2')
		return true;
	return false;
}

void	check_door(void *param)
{
	t_game *game;

	game = param;
	if (door_is_near(game->map, game->player.pos))
		game->images.door_help->enabled = true;
	else
		game->images.door_help->enabled = false;
}

void	try_open(char **map, t_vector pos)
{
	int	new_x;
	int	new_y;

	new_x = (int) pos.x;
	new_y = (int) pos.y;
	if (map[new_y - 1][new_x] == '2')
		map[new_y - 1][new_x] = '0';
	else if (map[new_y + 1][new_x] == '2')
		map[new_y + 1][new_x] = '0';
	else if (map[new_y][new_x - 1] == '2')
		map[new_y][new_x - 1] = '0';
	else if (map[new_y][new_x + 1] == '2')
		map[new_y][new_x + 1] = '0';
}

void	open_door(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
	{
		try_open(game->map, game->player.pos);
		game->player.has_moved = true; // refreshes frame when E is pressed ;D
	}
}

void	load_door(t_game *game)
{
	mlx_texture_t *texture;

	texture = mlx_load_png("./textures/tknibbe.png");
	if (!texture)
		ft_error_and_exit("mlx_load_png() failed\n");
	game->textures.door = texture;

	game->images.door_help = mlx_put_string(game->mlx, "press 'E' to open door", WIDTH / 2 - 100, HEIGHT - 100);
	if (!game->images.door_help)
		ft_error_and_exit("mlx_load_png messed up man :(\n");
	game->images.door_help->enabled = false;
} 
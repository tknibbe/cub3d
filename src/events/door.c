/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:22:31 by tymonknibbe       #+#    #+#             */
/*   Updated: 2024/02/14 15:49:24 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DOOR_CLOSED '2'
#define DOOR_OPENED '3'

int	door_is_near(char **map, t_vector pos, char door_status)
{
	int	new_x;
	int	new_y;

	new_x = (int) pos.x;
	new_y = (int) pos.y;
	if (map[new_y - 1][new_x] == door_status ||
		map[new_y + 1][new_x] == door_status ||
		map[new_y][new_x - 1] == door_status ||
		map[new_y][new_x + 1] == door_status)
		return (true);
	return (false);
}

void	check_door(void *param)
{
	t_game	*game;

	game = param;
	if (door_is_near(game->map, game->player.pos, DOOR_CLOSED))
		game->images.door_open_text->enabled = true;
	else
		game->images.door_open_text->enabled = false;
	if (door_is_near(game->map, game->player.pos, DOOR_OPENED))
		game->images.door_close_text->enabled = true;
	else
		game->images.door_close_text->enabled = false;
}

void	open_door(char **map, t_vector pos)
{
	int	new_x;
	int	new_y;

	new_x = (int) pos.x;
	new_y = (int) pos.y;
	if (map[new_y - 1][new_x] == DOOR_CLOSED)
		map[new_y - 1][new_x] = DOOR_OPENED;
	else if (map[new_y + 1][new_x] == DOOR_CLOSED)
		map[new_y + 1][new_x] = DOOR_OPENED;
	else if (map[new_y][new_x - 1] == DOOR_CLOSED)
		map[new_y][new_x - 1] = DOOR_OPENED;
	else if (map[new_y][new_x + 1] == DOOR_CLOSED)
		map[new_y][new_x + 1] = DOOR_OPENED;
}

void	close_door(char **map, t_vector pos)
{
	int	new_x;
	int	new_y;

	new_x = (int) pos.x;
	new_y = (int) pos.y;
	if (map[new_y - 1][new_x] == DOOR_OPENED)
		map[new_y - 1][new_x] = DOOR_CLOSED;
	else if (map[new_y + 1][new_x] == DOOR_OPENED)
		map[new_y + 1][new_x] = DOOR_CLOSED;
	else if (map[new_y][new_x - 1] == DOOR_OPENED)
		map[new_y][new_x - 1] = DOOR_CLOSED;
	else if (map[new_y][new_x + 1] == DOOR_OPENED)
		map[new_y][new_x + 1] = DOOR_CLOSED;
}

bool	door_status(char **map, t_vector pos, char stat)
{
	int	new_x;
	int	new_y;

	new_x = (int) pos.x;
	new_y = (int) pos.y;
	if (map[new_y - 1][new_x] == stat)
		return (true);
	else if (map[new_y + 1][new_x] == stat)
		return (true);
	else if (map[new_y][new_x - 1] == stat)
		return (true);
	else if (map[new_y][new_x + 1] == stat)
		return (true);
	return (false);
}

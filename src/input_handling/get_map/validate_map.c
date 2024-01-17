/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:41:48 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 16:20:59 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"

static void	check_whole_line(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	if (x == 0 || x == game->map_rows -1)
	{
		while (i < game->map_cols)
		{
			if (game->map[x][i] != '1' && game->map[x][i] != ' ')
			{
				printf("[%c] %d && %d\n",game->map[x][i], x, i);
				ft_error_and_exit("Error, unclosed edge found\n");
			}
			i++;
		}
	}
	i = 0;
	if (y == 0 || y == game->map_cols -1)
	{
		while (i < game->map_rows -1)
		{
			if (game->map[i][y] != '1' && game->map[i][y] != ' ')
				ft_error_and_exit("Error, unclosed edge found\n");
			i++;
		}
	}
}

int	check_surroundings(t_game *game, int x, int y)
{
	const int	adjecent_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	const int	adjecent_y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int			i;
	int			new_x;
	int			new_y;

	i = 0;
	while (i < 8)
	{
		new_x = x + adjecent_x[i];
		new_y = y + adjecent_y[i];
		if ((new_x >= 0 && new_x < game->map_rows) && \
			(new_y >= 0 && new_y < game->map_cols))
		{
			if (game->map[new_x][new_y] != '1' && \
				game->map[new_x][new_y] != ' ')
				ft_error_and_exit("Error, map is invalid\n");
		}
		i++;
	}
	return (0);
}

void	find_player(char **map)
{
	int	x;
	int	y;
	int	player;

	x = 0;
	y = 0;
	player = 0;
	while (map[x])
	{
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || \
				map[x][y] == 'W' || map[x][y] == 'E')
				player++;
			y++;
		}
		y = 0;
		x++;
	}
	if (player == 1)
		return ;
	if (player > 1)
		ft_error_and_exit("Error, too many player positions found\n");
	ft_error_and_exit("Error, no player found\n");
}

void	print_map(char **map)
{
	int	i, j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	validate_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	print_map(game->map);
	check_whole_line(game, 0, 0);
	check_whole_line(game, game->map_rows - 1, game->map_cols -1);
	while (game->map[x])
	{
		while (game->map[x][y])
		{
			if (game->map[x][y] == ' ')
				check_surroundings(game, x, y);
			y++;
		}
		y = 0;
		x++;
	}
	find_player(game->map);
	return (0);
}

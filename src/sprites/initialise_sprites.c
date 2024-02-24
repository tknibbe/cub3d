/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_sprites.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 15:25:31 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/14 15:25:31 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>
#include "libft.h"

static int	count_nr_empty_spots(char **map)
{
	int	x;
	int	y;
	int	empty_spots;

	y = 0;
	empty_spots = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0')
				empty_spots++;
			x++;
		}
		y++;
	}
	return (empty_spots);
}

// fills our empty spot array with the coordinates of eveyr possible
// empty spot
static void	fill_spots(t_coords *empty_spots, char **map)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0')
			{
				empty_spots[i].x = x;
				empty_spots[i].y = y;
				i++;
			}
			x++;
		}
		y++;
	}
}

// counts amount of empty spots, makes an array of the empty spots coordinates
// then randomises a given amount of spots to fill with sprite types
// then adds cheerleaders and lamps base don the randomised values
void	initialise_sprites(t_game *game)
{
	int			nr_empty_spots;
	t_coords	*empty_spots;

	nr_empty_spots = count_nr_empty_spots(game->map);
	empty_spots = ft_calloc(nr_empty_spots, sizeof(t_coords));
	if (empty_spots == NULL)
		ft_error_and_exit("Malloc failure\n");
	fill_spots(empty_spots, game->map);
	randomise_sprites_positions(empty_spots, nr_empty_spots);
	initialise_cheerleaders(game, empty_spots, nr_empty_spots);
	initialise_lamps(game, empty_spots, nr_empty_spots);
	initialise_enemies(game);
	calc_dist(game->player.pos, game->sprites, game->sprite_nr);
	sort_sprites(game->sprites, game->sprite_nr);
	free(empty_spots);
}

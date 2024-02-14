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

int	count_empty_spots(char **map)
{
	int	x;
	int	y;
	int	empty_spots;

	y = 0;
	empty_spots = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while(map[y][x] != '\0')
		{
			if (map[y][x] == '0')
				empty_spots++;
			x++;
		}
		y++;
	}
	return (empty_spots);
}

void	fill_spots(t_coords *empty_spots, char **map)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while(map[y][x] != '\0')
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

bool	already_rolled(int rolled_number, int *selected_numbers, int i)
{
	while (i > 0)
	{
		if (rolled_number == selected_numbers[i])
			return (true);
		i--;
	}
	return (false);
}

void	randomise_sprites(t_coords *empty_spots, int empty_spots_nr)
{
	int	i;
	int	*selected_numbers;
	int	random_number;

	selected_numbers = ft_calloc(empty_spots_nr / 4, sizeof(int));
	i = 0;
	srand(time(NULL));
	while (i < empty_spots_nr)
	{
		random_number = rand() % empty_spots_nr;
		if (already_rolled(random_number, selected_numbers, i))
			continue ;
		empty_spots[random_number].type = (rand() % 2) + 1;
		selected_numbers[i] = random_number;
		i++;
	}
}

void	add_lamps(t_sprite new_sprite, t_game *game, t_coords *empty_spots_coordinates, int empty_spots_nr)
{
	int	i;

	i = 0;
	while (i < empty_spots_nr)
	{
		if (new_sprite.type == empty_spots_coordinates[i].type)
		{
			new_sprite.x = empty_spots_coordinates[i].x + 0.5;
			new_sprite.y = empty_spots_coordinates[i].y + 0.5;
			add_sprite(game, new_sprite);
		}
		i++;
	}
}

void	initialise_sprites(t_game *game)
{
	t_sprite	new_sprite;

	int	empty_spots = count_empty_spots(game->map);
	t_coords 	*empty_spots_coordinates = ft_calloc(empty_spots, sizeof(t_coords));
	if (empty_spots_coordinates == NULL)
		ft_error_and_exit("Malloc failure\n");
	fill_spots(empty_spots_coordinates, game->map);
	randomise_sprites(empty_spots_coordinates, empty_spots);
	int count = 0;
	for (int i = 0; i < empty_spots; i++)
	{
		if (empty_spots_coordinates[i].type != 0)
			count++;
//		printf("%d %d %d\n", empty_spots_coordinates[i].x, empty_spots_coordinates[i].y, empty_spots_coordinates[i].type);
	}
	printf("%d %d\n", empty_spots, count);


	new_sprite.sprite_scale = 2;
	new_sprite.texture_nbr = 2;
	new_sprite.type = LAMP;
	new_sprite.texture_cycle = malloc(8 * 2);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	new_sprite.curr_cycle = 0;
	new_sprite.x = 7.5;
	new_sprite.y = 7.5;
	new_sprite.texture_cycle[0] = mlx_load_png("textures/tymon_sprite_teeth.png");
	new_sprite.texture_cycle[1] = mlx_load_png("textures/tymon_sprite.png");
//	new_sprite.texture_cycle[2] = mlx_load_png("textures/tymon.png");
	*new_sprite.tex = *new_sprite.texture_cycle[0];

	new_sprite.height_offset = -new_sprite.tex->height;
	add_lamps(new_sprite, game, empty_spots_coordinates, empty_spots);
//	add_sprite(game, new_sprite);
//	new_sprite.x = 8.5;
//	new_sprite.y = 7.5;
//	add_sprite(game, new_sprite);
//	new_sprite.x = 9.5;
//	new_sprite.y = 7.5;

//	add_sprite(game, new_sprite);
//	new_sprite.x = 10.5;
//	new_sprite.y = 7.5;
	new_sprite.type = CHEERLEADER;
	new_sprite.texture_cycle = malloc(8 * 3);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	new_sprite.texture_cycle[0] = mlx_load_png("textures/tymon_sprite_teeth.png");
	new_sprite.texture_cycle[1] = mlx_load_png("textures/tymon_sprite.png");
//	new_sprite.texture_cycle[2] = mlx_load_png("textures/tymon.png");
	*new_sprite.tex = *new_sprite.texture_cycle[0];
	new_sprite.height_offset = new_sprite.tex->height;
	new_sprite.curr_cycle = 1;
	add_lamps(new_sprite, game, empty_spots_coordinates, empty_spots);

//	add_sprite(game, new_sprite);
//	new_sprite.x = 11.5;
//	new_sprite.y = 7.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 7.5;
//	new_sprite.y = 8.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 7.5;
//	new_sprite.y = 1.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 8.5;
//	new_sprite.y = 8.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 9.5;
//	new_sprite.y = 8.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 10.5;
//	new_sprite.y = 8.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 11.5;
//	new_sprite.y = 8.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 12.5;
//	new_sprite.y = 1.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 11.5;
//	new_sprite.y = 1.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 1.5;
//	new_sprite.y = 1.5;
//
//	add_sprite(game, new_sprite);
//	new_sprite.x = 10.5;
//	new_sprite.y = 1.5;
//
//	add_sprite(game, new_sprite);
}


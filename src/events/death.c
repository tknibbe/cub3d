/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/17 16:37:56 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/17 16:37:56 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <unistd.h>

#define ENEMY '4'

static bool	adjust_alpha_until_max(mlx_image_t *you_lost)
{
	static int		time;
	unsigned int	x;
	unsigned int	y;

	if (time == 63)
		return (true);
	y = 0;
	while (y < you_lost->height)
	{
		x = 0;
		while (x < you_lost->width)
		{
			you_lost->pixels[(y * you_lost->width + x) * 4 + 3] = time * 4;
			x++;
		}
		y++;
	}
	time++;
	return (false);
}

static void	display_string(t_game *game)
{
	game->images.game_over = mlx_put_string(game->mlx, "lol you lose", \
											HALF_WIDTH - 250, HALF_HEIGHT);
	if (game->images.game_over == NULL)
		ft_mlx_error_and_exit(game);
	if (mlx_resize_image(game->images.game_over, 500, 200) == false)
		ft_mlx_error_and_exit(game);
	mlx_set_instance_depth(game->images.game_over->instances, 2);
}

static void	display_death_screen(t_game *game)
{
	mlx_texture_t	*lost_texture;

	lost_texture = mlx_load_png("textures/gameover.png");
	if (lost_texture == NULL)
		display_string(game);
	else
	{
		game->images.game_over = mlx_texture_to_image(game->mlx, lost_texture);
		if (game->images.game_over == NULL)
			ft_mlx_error_and_exit(game);
		if (mlx_image_to_window(game->mlx, game->images.game_over, 0, 0) == -1)
			ft_mlx_error_and_exit(game);
	}
	adjust_alpha_until_max(game->images.game_over);
	if (lost_texture != NULL)
		mlx_delete_texture(lost_texture);
}

static bool	colided_with_enemy(t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)game->player.pos.x;
	map_y = (int)game->player.pos.y;
	if (game->map[map_y][map_x] == ENEMY && \
		fabs((double)map_x + 0.5 - game->player.pos.x) < 0.25 && \
		fabs((double)map_y + 0.5 - game->player.pos.y) < 0.25 && \
		identify_enemy(game, map_x, map_y) != (int)game->player.state)
	{
		display_death_screen(game);
		game->player.is_dead = true;
		return (true);
	}
	return (false);
}

bool	check_death(t_game *game)
{
	if (game->player.is_dead == true)
	{
		if (adjust_alpha_until_max(game->images.game_over) == true)
		{
			mlx_close_window(game->mlx);
			sleep(2);
		}
		return (true);
	}
	if (colided_with_enemy(game) == true)
		return (true);
	return (false);
}

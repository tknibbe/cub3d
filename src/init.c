/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:22:36 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/02/05 15:20:17 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static void	initialise_icon(t_game *game)
{
	game->textures.icon = mlx_load_png("./textures/jan.png");
	if (!game->textures.icon)
		ft_mlx_error_and_exit(game);
	mlx_set_icon(game->mlx, game->textures.icon);
}

static void	initialise_images(t_game *game)
{
	game->images.fps = mlx_put_string(game->mlx, "FPS 59", 20, 20);
	if (game->images.fps == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
	game->images.maze = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->images.maze == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
	ray_caster(game);
	mlx_image_to_window(game->mlx, game->images.maze, 0, 0);
}

void	initialise_game(t_game *game, char *title)
{
//	mlx_win_cursor_t	*cursor;

	game->mlx = mlx_init(WIDTH, HEIGHT, title, true);
	if (game->mlx == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
	initialise_images(game);
	initialise_minimap(game, &game->minimap);
	initialise_player(game);
	initialise_icon(game);
	draw_sprites(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	load_door(game);
//	cursor = mlx_create_cursor(game->textures.east);


//	mlx_set_cursor(game->mlx, cursor);
//	mlx_destroy_cursor(cursor);
//	ray_caster(game);
}

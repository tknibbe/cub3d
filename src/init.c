/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:22:36 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/11 19:22:38 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	initialise_images(t_game *game)
{
	game->images.fps = mlx_put_string(game->mlx, "FPS 59", 20, 20);
	if (game->images.fps == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
//	draw_minimap(game);
	initialize_player(game);
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
	mlx_win_cursor_t	*cursor;

	game->mlx = mlx_init(WIDTH, HEIGHT, title, true);
	if (game->mlx == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
	initialise_images(game);
	cursor = mlx_create_cursor(game->textures.east);

//	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_cursor(game->mlx, cursor);
//	mlx_destroy_cursor(cursor);
//	ray_caster(game);
}

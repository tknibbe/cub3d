/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:22:36 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/02/15 17:22:13 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

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
	mlx_set_instance_depth(game->images.maze->instances, 1);
}

void	initialise_game(t_game *game, char *title)
{
//	mlx_win_cursor_t	*cursor;

	game->wall_distances = ft_calloc(WIDTH, sizeof(double)); //PROTECT
	game->img_buffer = malloc(sizeof(uint32_t) * (HEIGHT * WIDTH)); // PROTECT
	game->mlx = mlx_init(WIDTH, HEIGHT, title, true);
	if (game->mlx == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
	load_door(game);
	initialise_images(game);
	initialise_minimap(game, &game->minimap);
	initialise_player(game);
	initialise_icon(game);
	initialise_sprites(game);
	fix_textures(game);
	calc_dist(game->player.pos, game->sprites, game->sprite_nr);
	sort_sprites(game->sprites, game->sprite_nr);
	draw_sprites(game);
//	for(int i = 0; game->map[i]; i++)
//	{
//		printf("%s\n", game->map[i]);
//	}
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
//	cursor = mlx_create_cursor(game->textures.east);


//	mlx_set_cursor(game->mlx, cursor);
//	mlx_destroy_cursor(cursor);
//	ray_caster(game);
}

void	load_door(t_game *game)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./textures/tknibbe.png");
	if (!texture)
		ft_error_and_exit("mlx_load_png() failed\n");
	game->textures.door = texture;
	game->images.door_open_text = mlx_put_string(game->mlx, \
			"press 'E' to open door", WIDTH / 2 - 100, HEIGHT - 100);
	if (!game->images.door_open_text)
		ft_error_and_exit("mlx_load_png messed up man :(\n");
	game->images.door_open_text->enabled = false;
	mlx_set_instance_depth(game->images.door_open_text->instances, 2);


	game->images.door_close_text = mlx_put_string(game->mlx, \
			"press 'E' to close door", WIDTH / 2 - 100, HEIGHT - 100);
	if (!game->images.door_close_text)
		ft_error_and_exit("mlx_load_png messed up man :(\n");
	game->images.door_close_text->enabled = false;
	mlx_set_instance_depth(game->images.door_close_text->instances, 2);

}

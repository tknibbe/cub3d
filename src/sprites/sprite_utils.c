/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 15:21:32 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/11 15:21:32 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	print_sprites(t_sprite *sprites, int sprite_nr)
{
	int	i;

	i = 0;
	while (i < sprite_nr)
	{
		printf("%lf %lf %lf\n", sprites[i].x, sprites[i].y, sprites[i].dist_to_player);
		i++;
	}
	printf("\n");
}

void	calc_dist(t_vector player_pos, t_sprite *sprites, int sprite_nr)
{
	int		i;
	double	x_sq;
	double	y_sq;

	i = 0;
	while (i < sprite_nr)
	{
		x_sq = (player_pos.x - sprites[i].x) * (player_pos.x - sprites[i].x);
		y_sq = (player_pos.y - sprites[i].y) * (player_pos.y - sprites[i].y);
		sprites[i].dist_to_player = x_sq + y_sq;
		i++;
	}
}

void	resort_sprites(t_sprite *sprites, int sprite_nr)
{
	int			j;
	t_sprite	temp;

	j = 0;
	while (j < sprite_nr - 1)
	{
		if (sprites[j].dist_to_player < sprites[j + 1].dist_to_player)
		{
			temp = sprites[j];
			sprites[j] = sprites[j + 1];
			sprites[j + 1] = temp;
			break ;
		}
		j++;
	}
}

void	sort_sprites(t_sprite *sprites, int sprite_nr)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < sprite_nr - 1)
	{
		j = 0;
		while (j < sprite_nr - i - 1)
		{
			if (sprites[j].dist_to_player < sprites[j + 1].dist_to_player)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	add_sprite(t_game *game, t_sprite new_sprite)
{
	int			i;
	t_sprite	*new_sprites;

	new_sprites = ft_calloc(game->sprite_nr + 1, sizeof(t_sprite));
	if (new_sprites == NULL)
		ft_error_and_exit("Malloc failure\n");
	i = 0;
	while (i < game->sprite_nr)
	{
		new_sprites[i] = game->sprites[i];
		i++;
	}
	new_sprites[i] = new_sprite;
	game->sprite_nr++;
	free(game->sprites);
	game->sprites = new_sprites;
}

void	initialise_sprites(t_game *game)
{
	t_sprite	new_sprite;

	new_sprite.sprite_scale = 2;
	new_sprite.texture_nbr = 2;
	new_sprite.texture_nbr = 0;
	new_sprite.type = LAMP;
	new_sprite.texture_cycle = malloc(8 * 2);
	new_sprite.tex = malloc(sizeof(mlx_texture_t));
	new_sprite.curr_cycle = 0;
	new_sprite.x = 7.5;
	new_sprite.y = 7.5;
	new_sprite.texture_cycle[0] = mlx_load_png("textures/tymon_sprite_teeth.png");
	new_sprite.texture_cycle[1] = mlx_load_png("textures/tymon_sprite.png");
	*new_sprite.tex = *new_sprite.texture_cycle[0];

	new_sprite.height_offset = -new_sprite.tex->height;
	add_sprite(game, new_sprite);
	new_sprite.x = 8.5;
	new_sprite.y = 7.5;
	add_sprite(game, new_sprite);
	new_sprite.x = 9.5;
	new_sprite.y = 7.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 10.5;
	new_sprite.y = 7.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 11.5;
	new_sprite.y = 7.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 7.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 7.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 8.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 9.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 10.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 11.5;
	new_sprite.y = 8.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 12.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 11.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 1.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
	new_sprite.x = 10.5;
	new_sprite.y = 1.5;

	add_sprite(game, new_sprite);
}

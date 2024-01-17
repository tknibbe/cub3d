/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:00:02 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/13 16:53:37 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static char	*create_fps_string(int fps)
{
	char	*fps_string;

	fps_string = ft_itoa(fps);
	if (fps_string == NULL)
	{
		ft_error_and_exit("cub3d: Memory allocation failure\n");
	}
	fps_string = ft_strjoin_free_second("FPS: ", fps_string);
	if (fps_string == NULL)
	{
		ft_error_and_exit("cub3d: Memory allocation failure\n");
	}
	return(fps_string);
}

static void	replace_image(t_game *game, int fps)
{
	char	*fps_string;

	fps_string = create_fps_string(fps);
	mlx_delete_image(game->mlx, game->images.fps);
	game->images.fps = mlx_put_string(game->mlx, fps_string, 20, 20);
//	game->images.fps->instances[0].z = 0;
	free(fps_string);
	if (game->images.fps == NULL)
	{
		ft_mlx_error_and_exit(game);
	}
}

void	fps_counter(void *param)
{
	static int		fps;
	static double	previous_time;
	t_game			*game;

	game = param;
	if (mlx_get_time() < previous_time + 1)
	{
		fps++;
	}
	else
	{
		replace_image(game, fps);
		fps = 0;
		previous_time = mlx_get_time();
	}
}

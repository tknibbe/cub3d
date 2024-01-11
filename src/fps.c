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

void	fps_counter(void *mlxshit)
{
	static int		fps;
	static double	current_time;
	t_game			*mlx;
	char 			*fps_string;

	mlx = mlxshit;
	if (!current_time)
	{
		current_time = mlx_get_time();
		mlx->images.fps = mlx_put_string(mlx->mlx, "FPS 60", 20, 20);
	}
	if (mlx_get_time() < current_time + 1)
	{
		fps++;
	}
	else
	{
		mlx_delete_image(mlx->mlx, mlx->images.fps);
		fps_string = ft_itoa(fps);
		mlx->images.fps = mlx_put_string(mlx->mlx, fps_string, 20, 20);
		free(fps_string);
		fps = 0;
		current_time = mlx_get_time();
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:00:02 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/01 16:00:46 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fps_counter(void *mlxshit)
{
	//calculate fps every second
	static int		fps;
	static double	starttime;

	if (!starttime)
	{
		starttime = mlx_get_time();
	}
	if (mlx_get_time() < starttime + 1)
	{
		fps++;
	}
	else
	{
		printf("%d fps\n", fps);
		mlx_put_string(mlxshit, ft_itoa(fps), rand() % 1000, rand() % 1000);
		fps = 0;
		starttime = mlx_get_time();
	}

	//calculate fps for every frame
	static double	test;
	double leftover = mlx_get_time() - test;
	// printf("%f frames\n", 1 / leftover);
	test = mlx_get_time();
	mlx_put_string(mlxshit, ft_itoa(1 / leftover), rand() % 1000, rand() % 1000);
}
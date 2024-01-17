/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:20:59 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/17 19:21:00 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	static double	last_x;
	t_game			*game;

	(void)ypos;
	game = param;
	if (last_x > xpos)
		rotate(&game->player, 1);
	else
		rotate(&game->player, -1);
	last_x = xpos;
	//	(void)param;

//	printf("%lf %lf\n", xpos, ypos);
}

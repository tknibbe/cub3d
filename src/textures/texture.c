/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:10:57 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/22 20:41:46 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h> //debug

#define RED		0xFF0000FF
#define GREEN	0x00FF00FF

void	buffer_to_img(int *buffer, mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// printf("heck\n");
			// printf("%X\n", buffer[x * HEIGHT + y]);
			mlx_put_pixel(img, x, y, buffer[x * HEIGHT + y]);
			y++;
		}
		x++;
	}
}

void	line_to_buffer(int *buffer, t_game *game, t_ray ray_vars, int x)
{
	int	y;

	y = 0;


	(void) game;

	//find wall dimensions
	int	wall_height;
	int	start_y;
	int	end_y;

	wall_height = (int)(HEIGHT / ray_vars.dist_to_wall);
	start_y = -wall_height / 2 + HEIGHT / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = wall_height / 2 + HEIGHT / 2;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;


	//draw ceiling until top of wall
	while (y < start_y)
	{
		buffer[x * HEIGHT + y] = RED;
		y++;
	}
	//draw wall
	while (y < end_y)
	{
		buffer[x * HEIGHT + y] = GREEN; //get_pixel_colour();
		y++;
	}
	//draw floor
	while (y < HEIGHT)
	{
		buffer[x * HEIGHT + y] = RED;
		y++;
	}
	
	
}
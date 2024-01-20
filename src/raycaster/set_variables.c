/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:02:37 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/17 20:02:38 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// sets the distance the ray travels when going from one side of the block
// to the other side of the block in the x and y axis.
// so f.e. from point x=1 to x=2
// we avoid division by 0 and if that's the case we set to variable
// to a big number (division by a number close to 0 gives a very biiiiig number
static void	set_block_distance(t_ray *ray_vars)
{
	if (ray_vars->ray.x == 0)
		ray_vars->block_dist.x = 1000000000;
	else
		ray_vars->block_dist.x = fabs(1 / ray_vars->ray.x);
	if (ray_vars->ray.y == 0)
		ray_vars->block_dist.y = 1000000000;
	else
		ray_vars->block_dist.y = fabs(1 / ray_vars->ray.y);
}

// sets the starting distance of the ray from the position of the player to
// the x or y axis that it would first encounter, also sets which direction
// we are stepping to
// so f.e. if the direction of our ray.x is negative,
// that means we travel to the left and to smaller x-es every time,
// therefore the step is -1 and the starting distance is our
// player pos - map position times the amount it takes to cover a block
// f.e. if player.pos is 1.5x, we're in map.x 1, so we have 1.5 - 1 = 0.5
// we then multiply 0.5 times the distance of block so half the distance
// which make sense if we move the other direction we are moving towards x=2
// so we need the distance between 1.5 and 2
// which is our map.x=1 + 1 = 2 - player.pos.x = 0.5
static void	set_start_dist_to_block(t_ray *r_v, t_player player)
{
	if (r_v->ray.x < 0)
	{
		r_v->step_dir_x = -1;
		r_v->side_dist.x = (player.pos.x - r_v->map_x) * r_v->block_dist.x;
	}
	else
	{
		r_v->step_dir_x = 1;
		r_v->side_dist.x = (r_v->map_x + 1 - player.pos.x) * r_v->block_dist.x;
	}
	if (r_v->ray.y < 0)
	{
		r_v->step_dir_y = -1;
		r_v->side_dist.y = (player.pos.y - r_v->map_y) * r_v->block_dist.y;
	}
	else
	{
		r_v->step_dir_y = 1;
		r_v->side_dist.y = (r_v->map_y + 1 - player.pos.y) * r_v->block_dist.y;
	}
}

// camerax is the coordinate on the screen converted form pixels to a value
// between -1 and 1
// ray.x and ray.y are the coordinates of the ray vector
// map.x and map.y are just the integer values of which block we're
// currently in f.e.
// if player position is (1.232, 8.9) we're in block (1,8)
void	setup_ray_vars(t_ray *ray_vars, t_player player, int screen_x)
{
	ray_vars->camerax = ((double)(2 * screen_x) / WIDTH) - 1;
	ray_vars->ray.x = player.dir.x + player.plane.x * ray_vars->camerax;
	ray_vars->ray.y = player.dir.y + player.plane.y * ray_vars->camerax;
	ray_vars->map_x = (int)player.pos.x;
	ray_vars->map_y = (int)player.pos.y;
	set_block_distance(ray_vars);
	set_start_dist_to_block(ray_vars, player);
}

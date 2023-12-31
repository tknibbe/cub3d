/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:23:25 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/07 16:56:44 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1000
# define HEIGHT 1000

# include "MLX42.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	int				floor;
	int				ceiling;
}	t_textures;

typedef struct	s_player
{
	int		x; //decide on what kind of varbiable this shoudl be
	int		y;
	float	orientation;
	int		fov;
}	t_player;

typedef struct	s_game
{
	char		**map;
	int			map_cols;
	int			map_rows;
	t_textures	textures;
	t_player	player;
}	t_game;


void	key_hook(void *param);

#endif
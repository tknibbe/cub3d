/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmolenaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:38:02 by jmolenaa          #+#    #+#             */
/*   Updated: 2024/01/21 15:38:03 by jmolenaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

# define MAX_MINIMAP_PIXELS 200
# define MARGIN 40
# define CUBE_SIDE 8
# define PLAYER_SIZE 4
# define MAX_MINIMAP_BLOCKS 25.0
# define MINIMAP_PIXEL_STEP 0.125

typedef struct s_game	t_game;
typedef struct s_vector	t_vector;

typedef struct s_minimap
{
	int			width;
	int			height;
	mlx_image_t	*img;
}	t_minimap;

void	draw_player(t_game *game, t_minimap *minimap, t_vector start);
void	initialise_minimap(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game, t_minimap *minimap);

#endif

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

# define MAX_MINIMAP_SIDE 200
# define MARGIN 40
# define CUBE_SIDE 8

typedef struct s_game t_game;

typedef struct s_minimap
{
	int	width;
	int	height;
}	t_minimap;

void	draw_minimap(t_game *game);

#endif

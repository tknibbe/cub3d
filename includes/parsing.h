/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:17:53 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/07 16:49:36 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include "cub3d.h"

typedef struct s_map t_map;

typedef struct s_map
{
	char	*line;
	t_map	*next;
}	t_map;


int		get_input(t_game *game, char *filename);
int		get_textures(t_textures *textures, int fd);
void	get_map(t_game *game, int fd);
int		valid_file_name(char *file, char *extension);
int		protected_open(char *file);

t_map	*ft_lstnew_map(void *content);
void	ft_mapadd_back(t_map **lst, t_map *new_node);
int		map_lstsize(t_map *lst);
void	free_map(t_map *map);

void	change_to_dp(t_map *temp_map, t_game *game);

int		validate_map(t_game *game);
#endif
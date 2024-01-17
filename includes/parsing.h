/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:17:53 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 14:15:52 by tknibbe          ###   ########.fr       */
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

# define NO 0
# define EA 1
# define SO 2
# define WE 3
# define F	4
# define C	5
# define TRANSPARANCY 255

int		get_input(t_game *game, char *filename);
void	get_textures(t_textures *textures, int fd);
void	get_map(t_game *game, int fd);
int		valid_file_name(char *file, char *extension);
int		protected_open(char *file);

t_map	*ft_lstnew_map(void *content);
void	ft_mapadd_back(t_map **lst, t_map *new_node);
int		map_lstsize(t_map *lst);
void	free_map(t_map *map);

void	change_to_dp(t_map *temp_map, t_game *game);

int		validate_map(t_game *game);

void	not_all_textures_set(t_textures *t);
void	check_double_texture(t_textures *text, int cat);
int		valid_rgb_value(char *s);
int		count_rgb(int state);
int		calculate_rgb(char **nums);
#endif
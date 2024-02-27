/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:17:53 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/27 18:05:27 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include "cub3d.h"

# define FLOOR			'0'
# define WALL			'1'
# define DOOR_CLOSED	'2'
//could change to '9' or something for map making logic.
//not allowed in map making and no user interaction vvvv
# define DOOR_OPEN		'3'
# define ENEMY			'4'
# define NO 0
# define EA 1
# define SO 2
# define WE 3
# define F	4
# define C	5
# define TRANSPARANCY 255

typedef struct s_map	t_map;

typedef struct s_map
{
	char	*line;
	t_map	*next;
}	t_map;

int		get_input(t_game *game, char *filename);
void	get_textures(t_textures *textures, int fd);
void	get_map(t_game *game, int fd);
int		valid_file_name(char *file, char *extension);
int		protected_open(char *file);
void	free_double_pointer(char **ptr);

t_map	*ft_lstnew_map(void *content);
void	ft_mapadd_back(t_map **lst, t_map *new_node);
int		map_lstsize(t_map *lst);
void	free_map(t_map *map);

void	change_to_dp(t_map *temp_map, t_game *game);

int		validate_map(t_game *game);
void	set_player(t_player *player, int x, int y, char dir);

void	not_all_textures_set(t_textures *t);
void	check_double_texture(t_textures *text, int cat);
int		get_rgb(char *line);
int		valid_rgb_value(char *s);
int		count_rgb(int state);
int		calculate_rgb(char **nums);
int		check_f_and_c(t_textures *text, char *line);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:17:53 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/02 16:27:16 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include "cub3d.h"

int	get_input(t_game *game, char *filename);
int	get_textures(t_textures *textures, int fd);
int	valid_file_name(char *file, char *extension);
int	protected_open(char *file);
#endif
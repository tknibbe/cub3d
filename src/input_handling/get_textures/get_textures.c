/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:33:50 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/27 18:05:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"
#include "MLX42.h"
#include <errno.h>

#define SETF 0
#define SETC 1

static void	put_in_struct(t_textures *text, char *path, int cat)
{
	mlx_texture_t	*texture;

	check_double_texture(text, cat);
	texture = mlx_load_png(path);
	if (!texture)
		ft_error_and_exit("mlx_load_png() failed\n");
	if (cat == NO)
		text->north = texture;
	if (cat == EA)
		text->east = texture;
	if (cat == WE)
		text->west = texture;
	if (cat == SO)
		text->south = texture;
}

static int	add_line(t_textures *text, char *line, int categorie)
{
	char	**text_fn;
	int		i;

	i = 0;
	text_fn = ft_split(line, ' ');
	if (!text_fn)
		ft_error_and_exit("ft_split() allocation went wrong\n");
	if (!text_fn[1])
		ft_error_and_exit("Error, no texture location found\n");
	if (valid_file_name(&text_fn[1][i], ".png"))
		ft_error_and_exit("Wrong texture file extension (only .png)\n");
	while (text_fn[i + 1])
	{
		i++;
	}
	if (i != 1)
		ft_error_and_exit("Error, too many texture arguments\n");
	put_in_struct(text, &text_fn[1][0], categorie);
	free_double_pointer(text_fn);
	return (EXIT_SUCCESS);
}

static int	valid_and_add_line(t_textures *text, char *line)
{
	int	i;

	i = 0;
	if (!line[0])
		return (EXIT_FAILURE);
	while (ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(line, "NO ", 3))
		return (add_line(text, line, NO));
	else if (!ft_strncmp(line, "EA ", 3))
		return (add_line(text, line, EA));
	else if (!ft_strncmp(line, "SO ", 3))
		return (add_line(text, line, SO));
	else if (!ft_strncmp(line, "WE ", 3))
		return (add_line(text, line, WE));
	else if (!check_f_and_c(text, line))
		return (EXIT_SUCCESS);
	ft_error_and_exit("Error, wrong texture delimiter found\n");
	return (EXIT_FAILURE);
}

void	get_textures(t_textures *textures, int fd)
{
	int		textures_found;
	char	*line;

	textures_found = 0;
	while (textures_found < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = ft_strdel(line, "\t\n\v\r");
		if (!line)
			ft_error_and_exit("Malloc() failed in ft_strdel\n");
		if (!valid_and_add_line(textures, line))
			textures_found++;
		free(line);
	}
	if (errno != 0)
		ft_error_and_exit("Malloc failure\n");
	not_all_textures_set(textures);
}

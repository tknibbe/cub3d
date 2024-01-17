/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:33:50 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 16:31:32 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"
#include "MLX42.h"
#include <unistd.h> //

#define SETF 0
#define SETC 1

static int	get_rgb(char *line)
{
	int		i;
	char	**nums;
	int		ret;

	i = 0;
	if (line[i] == 'F')
		count_rgb(SETF);
	else
		count_rgb(SETC);
	i++;
	while (ft_isspace(line[i]))
		i++;
	nums = ft_split(&line[i], ',');
	if (!nums)
		ft_error_and_exit("Malloc() failed in ft_split()\n");
	ret = calculate_rgb(nums);
	ft_free_array(nums);
	return (ret);
}

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
	if (valid_file_name(&text_fn[1][i], ".png") && \
		valid_file_name(&text_fn[1][i], ".xpm42")) //idk bout xpm42. look at it later
		ft_error_and_exit("Wrong file extension\n");
	put_in_struct(text, &text_fn[1][i], categorie);
	while (text_fn[i])
	{
		free (text_fn[i]);
		i++;
	}
	free(text_fn);
	return (EXIT_SUCCESS);
}

static int	valid_and_add_line(t_textures *text, char *line) //make it return true if a texture is found
{
	int	i;

	i = 0;
	if (!line[0])
		return (EXIT_FAILURE);
	while (ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "NO", 2))
		return(add_line(text, line, NO));
	else if (!ft_strncmp(&line[i], "EA", 2))
		return(add_line(text, line, EA));
	else if (!ft_strncmp(&line[i], "SO", 2))
		return(add_line(text, line, SO));
	else if (!ft_strncmp(&line[i], "WE", 2))
		return(add_line(text, line, WE));
	else if (!ft_strncmp(&line[i], "F", 1))
	{
		text->floor = get_rgb(line);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(&line[i], "C", 1))
	{
		text->ceiling = get_rgb(line);
		return (EXIT_SUCCESS);
	}
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
	printf("%d textures found\n", textures_found);
	printf("north	%p\n", textures->north);
	printf("east	%p\n", textures->east);
	printf("south	%p\n", textures->south);
	printf("west 	%p\n", textures->west);
	printf("floor 	0x%X (%d)\n", textures->floor, textures->floor);
	printf("ceiling 0x%X (%d)\n\n", textures->ceiling, textures->ceiling);
	not_all_textures_set(textures);
}

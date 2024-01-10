/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:33:50 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/10 16:47:58 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"
#include "MLX42.h"

static unsigned int	more_function_here(char **nums)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	num;

	i = 0;
	while (nums[i])
	{
		valid_rgb_value(nums[i]);
		nums[i] = ft_strdel(nums[i], " ");
		num = ft_atoi(nums[i]);
		if (num > 255 || num < 0)
			break ;
		i++;
	}
	if (i != 3)
	{
		printf("Error, rgb value is fucked up g, fix this errormessage btw\n");
		exit (27);//
	}
	r = ft_atoi(nums[0]);
	g = ft_atoi(nums[1]);
	b = ft_atoi(nums[2]);
	return  ((r << 16) | (g << 8) | (b << 8) + TRANSPARANCY);
}

static int	get_rgb(t_textures *text, char *line)
{
	int		i;
	char	**nums;
	int		ret;

	i = 0;
	if ((line[i] == 'F' && text->floor != -1) || \
		line[i] == 'C' && text->ceiling != -1)
	{
		printf("double F/C found, replace this message\n");
		exit(1);
	}
	i++;
	while (ft_isspace(line[i]))
		i++;
	nums = ft_split(&line[i], ',');
	if (!nums)
		exit(27);//fix
	ret = more_function_here(nums);
	i = 0;
	while (nums[i])
	{
		free(nums[i]);
		i++;
	}
	free(nums);
	return (ret); //
}

static void put_in_struct(t_textures *text, char *path, int cat)
{
	mlx_texture_t *texture;

	check_double_texture(text, cat);
	texture = mlx_load_png(path);
	if (!texture)
		exit(27);//fix
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
		exit(27); //fix pls
	if (!text_fn[1])
	{
		printf("error, no texture location found for: %s\n(fix this error message)", line);
		exit(27); //fix
	}
	if (valid_file_name(&text_fn[1][i], ".png") && valid_file_name(&text_fn[1][i], ".xpm42")) //idk bout xpm42. look at it later
		exit(27);//fix
	put_in_struct(text, &text_fn[1][i], categorie);
	while (text_fn[i])
	{
		free (text_fn[i]);
		i++;
	}
	free(text_fn);
	return (EXIT_SUCCESS);
}

static int	valid_and_add_line(t_textures *text, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "NO", 2))
	{
		if (add_line(text, line, NO))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(&line[i], "EA", 2))
	{
		if (add_line(text, line, EA))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(&line[i], "SO", 2))
	{
		if (add_line(text, line, SO))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(&line[i], "WE", 2))
	{
		if (add_line(text, line, WE))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(&line[i], "F", 1))
		text->floor = get_rgb(text, line);
	else if (!ft_strncmp(&line[i], "C", 1))
		text->ceiling = get_rgb(text, line);
	else if (line[i])
	{
		printf("unknown texture delimiter found [%s]\n", &line[i]); // make error
		exit(1);
	}
	return (EXIT_SUCCESS);
}

void	get_textures(t_textures *textures, int fd)
{
	int		textures_found;
	char	*line;

	textures_found = 0;
	ft_memset(textures, 0, sizeof(t_textures));
	textures->floor = -1;
	textures->ceiling = -1;
	while (textures_found <= 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("ERROR RETRIEVING GNL, this error messsage needs to be replaced\
				\nif this error message shows it means you reached the EOF before finding all 6 \
				\ntextures. throw error here\n");
			exit(1);
		}
		line = ft_strdel(line, "\t\n\v\r");
		if (!line)
			exit(27);//fix
		if (!valid_and_add_line(textures, line))
			textures_found++;
		free(line);
	}
	printf("%d textures found\n", textures_found- 1);
	printf("north	%p\n", textures->north);
	printf("east	%p\n", textures->east);
	printf("south	%p\n", textures->south);
	printf("west 	%p\n", textures->west);
	printf("floor 	0x%X\n", textures->floor);
	printf("ceiling 0x%X\n\n", textures->ceiling);
	not_all_textures_set(textures);
}
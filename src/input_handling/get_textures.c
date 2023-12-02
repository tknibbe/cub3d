/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:33:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/02 18:09:32 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"
#include "MLX42.h"

# define NO 0
# define EA 1
# define SO 2
# define WE 3
# define F	4
# define C	5

static int	more_function_here(char **nums)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	num;

	i = 0;
	while (nums[i])
	{
		num = ft_atoi(nums[i]);
		if (num > 255 && nums < 0)
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
	return  (((r << 16) | (g << 8) | b) << 8) + 255;
}

static int	get_rgb(char *line)
{
	int		i;
	char	**nums;
	int		ret;

	i = 0;
	while (!ft_isdigit(line[i]))
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
	int		p;
	
	p = 0;
	text_fn = ft_split(line, ' ');
	if (!text_fn)
		exit(27); //fix pls
	if (valid_file_name(text_fn[1], ".png") && valid_file_name(text_fn[1], ".xpm42")) //idk bout xpm42. look at it later
		exit(27);//fix
	put_in_struct(text, text_fn[1], categorie);
	while (text_fn[p])
	{
		free (text_fn[p]);
		p++;
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
	{
		text->floor = get_rgb(line);
	}
	else if (!ft_strncmp(&line[i], "C", 1))
	{
		text->ceiling = get_rgb(line);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_textures(t_textures *textures, int fd)
{
	int		textures_found;
	char	*line;
	char	*trimline;

	ft_memset(textures, '0', sizeof(textures)); //maybe set all to null and ints to -1 and check at the end whether it was valid input
	textures_found = 0;
	while (textures_found < 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("ERROR RETRIEVING GNL, this error messsage needs to be replaced\n");
			// free acquired textures here
			return (EXIT_FAILURE);
		}
		trimline = ft_strtrim(line, "\n");
		if (!trimline)
			exit(27);//fix
		if (!valid_and_add_line(textures, trimline))
			textures_found++;
		free(line);
		free(trimline);
	}
	printf("%d textures found\n", textures_found);
	//check if ALL textures exist in the struct
	printf("north %p\n", textures->north);
	printf("east %p\n", textures->east);
	printf("south %p\n", textures->south);
	printf("west %p\n", textures->west);
	printf("floor %x\n", textures->floor);
	printf("ceiling %x\n", textures->ceiling);
	return (EXIT_SUCCESS);
}
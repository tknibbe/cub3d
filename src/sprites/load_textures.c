/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 15:50:03 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/19 15:50:03 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <dirent.h>
#include "libft.h"
#include <errno.h>

static int	count_entries(DIR *directory)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	errno = 0;
	entry = readdir(directory);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1))
			i++;
		entry = readdir(directory);
	}
	if (errno != 0)
		ft_exit_with_perror();
	if (i == 0)
		ft_error_and_exit("One of the texture directories is empty\n");
	return (i);
}

static void	load_entries(char *path, DIR *directory, t_sprite *new_sprite)
{
	struct dirent	*entry;
	char			*tex_path;
	int				i;

	errno = 0;
	i = 0;
	entry = readdir(directory);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1))
		{
			tex_path = ft_strjoin(path, entry->d_name);
			if (tex_path == NULL)
				ft_error_and_exit("Malloc failure\n");
			new_sprite->tex_cycle[i] = mlx_load_png(tex_path);
			free(tex_path);
			i++;
		}
		entry = readdir(directory);
	}
	if (errno != 0)
		ft_exit_with_perror();
}

static void	set_variables_and_allocate(t_sprite *new_sprite, int entry_amount)
{
	new_sprite->tex_cycle = ft_calloc(entry_amount, sizeof(mlx_texture_t *));
	new_sprite->tex_nb = entry_amount;
	new_sprite->tex = ft_calloc(1, sizeof(mlx_texture_t));
	if (new_sprite->tex_cycle == NULL || new_sprite->tex == NULL)
		ft_error_and_exit("Malloc failure\n");
}

void	load_textures(char *path, t_sprite *new_sprite)
{
	DIR	*directory;
	int	entry_amount;

	directory = opendir(path);
	if (directory == NULL)
		ft_exit_with_perror();
	entry_amount = count_entries(directory);
	set_variables_and_allocate(new_sprite, entry_amount);
	closedir(directory);
	directory = opendir(path);
	if (directory == NULL)
		ft_exit_with_perror();
	load_entries(path, directory, new_sprite);
	closedir(directory);
}

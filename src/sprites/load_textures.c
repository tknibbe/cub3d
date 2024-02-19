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

static void	load_entries(char *path, DIR *directory, char **entries)
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
			entries[i] = tex_path;
			i++;
		}
		entry = readdir(directory);
	}
	if (errno != 0)
		ft_exit_with_perror();
}

static void	set_vars(t_sprite *new_sprite, int entry_amount, char **entries)
{
	int	i;

	new_sprite->tex_cycle = ft_calloc(entry_amount, sizeof(mlx_texture_t *));
	new_sprite->tex_nb = entry_amount;
	new_sprite->tex = ft_calloc(1, sizeof(mlx_texture_t));
	if (new_sprite->tex_cycle == NULL || new_sprite->tex == NULL)
		ft_error_and_exit("Malloc failure\n");
	i = 0;
	while (entries[i] != NULL)
	{
		new_sprite->tex_cycle[i] = mlx_load_png(entries[i]);
		i++;
	}
}

static void	sort_entries(char **entries, int entry_nr, int path_l)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < entry_nr - 1)
	{
		j = 0;
		while (j < entry_nr - i - 1)
		{
			if (ft_atoi(entries[j] + path_l) > ft_atoi(entries[j + 1] + path_l))
			{
				temp = entries[j];
				entries[j] = entries[j + 1];
				entries[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	load_textures(char *path, t_sprite *new_sprite)
{
	DIR		*directory;
	int		entry_amount;
	char	**entries;

	directory = opendir(path);
	if (directory == NULL)
		ft_exit_with_perror();
	entry_amount = count_entries(directory);
	entries = ft_calloc(entry_amount + 1, sizeof(char *));
	if (entries == NULL)
		ft_error_and_exit("Malloc failure\n");
	closedir(directory);
	directory = opendir(path);
	if (directory == NULL)
		ft_exit_with_perror();
	load_entries(path, directory, entries);
	closedir(directory);
	sort_entries(entries, entry_amount, (int)ft_strlen(path));
	set_vars(new_sprite, entry_amount, entries);
	ft_free_array(entries);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:16:59 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 13:59:37 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int	protected_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "jammer\n", 8);
		write(STDERR_FILENO, "gaat mis bij openen van: ", 26);
		write(STDERR_FILENO, file, ft_strlen(file));
		write(STDERR_FILENO, "\n", 1);
		exit(errno);
	}
	return (fd);
}

int	valid_file_name(char *file, char *extension)
{
	int	ext_len;

	ext_len = ft_strlen(extension);
	if (ft_strncmp(&file[ft_strlen(file) - ext_len], \
		extension, ft_strlen(extension)))
	{
		write(STDERR_FILENO, "Error in the extension of your file\n", 37);
		write(STDERR_FILENO, "looking for : ", 15);
		write(STDERR_FILENO, extension, ext_len);
		write(STDERR_FILENO, "\nyou provided : ", 17);
		write(STDERR_FILENO, file, ft_strlen(file));
		write(STDERR_FILENO, "\n", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_input(t_game *game, char *filename)
{
	int	fd;

	if (valid_file_name(filename, ".cub"))
		ft_error_and_exit("Error, filename does not have the .cub extension\n");
	fd = protected_open(filename);
	get_textures(&game->textures, fd);
	get_map(game, fd);
	close(fd);
	return (EXIT_SUCCESS);
}

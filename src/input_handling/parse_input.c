/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:16:59 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/06 14:55:00 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int	protected_open(char *file) // moet ik hier nog meer protecten?
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
	if (ft_strncmp(&file[ft_strlen(file) - ext_len], extension, ft_strlen(extension)))
	{
		write(STDERR_FILENO, "Error in the extension of your file\n", 37); //debug 
		write(STDERR_FILENO, "looking for : ", 15);
		write(STDERR_FILENO, extension, ext_len);
		write(STDERR_FILENO, "\nyou privided : ", 17);
		write(STDERR_FILENO, file, ft_strlen(file));
		write(STDERR_FILENO, "\n",1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_input(t_game *game, char *filename)
{
	int	fd;

	ft_memset(game, 0, sizeof(game));
	if (valid_file_name(filename, ".cub"))
		exit(27); //fix
	fd = protected_open(filename);
	if (get_textures(&game->textures, fd)) // this leaves get_next_line directly after the last texture found. should work in get_map to immediately get the map data
		return(EXIT_FAILURE);
	get_map(game, fd); //moet nog ff geschreven worden
	close(fd);
	return (EXIT_SUCCESS);
}
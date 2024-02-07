/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:53:33 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/07 15:59:11 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"

static void	check_invalid_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'\
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ' \
			&& line[i] != '2')
			ft_error_and_exit("Error, invalid char found in map\n");
		i++;
	}
}

t_map	*put_in_linked_list(int fd)
{
	char	*line;
	t_map	*temp;
	t_map	*map;

	map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = ft_strdel(line, "\n");
		if (line[0])
		{
			check_invalid_chars(line);
			temp = ft_lstnew_map(line);
			ft_mapadd_back(&map, temp);
		}
		else
			free(line);
	}
	return (map);
}

void	get_map(t_game *game, int fd)
{
	t_map	*temp_map;

	temp_map = put_in_linked_list(fd);
	if (!temp_map)
		ft_error_and_exit("Error, No map found\n");
	change_to_dp(temp_map, game);
	validate_map(game);
	free_map(temp_map);
}

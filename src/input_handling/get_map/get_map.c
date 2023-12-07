/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:53:33 by tknibbe           #+#    #+#             */
/*   Updated: 2023/12/07 16:56:26 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "libft.h"

static int	valid_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1')
			return (1);
		i++;
	}
	return (0);
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
		{
			break ;
		}
		line = ft_strdel(line, "\n");
		if (!valid_chars(line))
		{
			free(line);
			continue;
		}
		temp = ft_lstnew_map(line);
		ft_mapadd_back(&map, temp);
	}
	return (map);
}

void print_2d(char **map) //debug 
{
	int	i = 0;
	
	while (map[i])
	{
		printf("%s [%zu]\n", map[i], ft_strlen(map[i]));
		i++;
	}
}



void	get_map(t_game *game, int fd)
{
	t_map	*temp_map;
	
	temp_map = put_in_linked_list(fd);
	if (!temp_map)
	{
		printf("ZIEKE ERROR G (geen mappie gevonden)\n");
		exit(27);//fix
	}
	change_to_dp(temp_map, game);
	print_2d(game->map); //debug
	validate_map(game);
	free_map(temp_map);
}

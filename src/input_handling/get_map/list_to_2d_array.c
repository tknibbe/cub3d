/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:20 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/10 16:55:39 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	adjust_string_lengths(t_game *game)
{
	size_t	max_len;
	int		i;
	char	*temp;
	
	max_len = 0;
	i = 0;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) > max_len)
			max_len = ft_strlen(game->map[i]);
		i++;
	}
	i = 0;
	while (game->map[i])
	{
		while (ft_strlen(game->map[i]) < max_len)	//ik heb persoonlijk problemen met deze aanpak maar ik had
											//geen zin om een nieuwe functie te schrijven die dit efficienter doet
		{
			
			temp = ft_strjoin(game->map[i], " ");
			free (game->map[i]);
			game->map[i] = temp;
		}
		i++;
	}
	game->map_cols = max_len;
}

static int	valid_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S'\
		 && str[i] != 'E' && str[i] != 'W' && str[i] != ' ')
		{
			printf("INVALID CHAR FOUND [%C]\n", str[i]);
		 	return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	change_to_dp(t_map *temp_map, t_game *game)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = map_lstsize(temp_map);
	ret = malloc(sizeof (char *) * (size + 1));
	if (!ret)
		exit(27);//fix
	ret[size] = NULL;
	while (i < size)
	{
		ret[i] = temp_map->line;
		// if (valid_chars(ret[i]))
		// 	exit(27);//fix
		i++;
		temp_map = temp_map->next;
	}
	game->map = ret;
	game->map_rows = size;
	adjust_string_lengths(game);
}

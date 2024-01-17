/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:20 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 16:31:50 by tknibbe          ###   ########.fr       */
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
		while (ft_strlen(game->map[i]) < max_len)
		//ik heb persoonlijk problemen met deze aanpak
		{
			temp = ft_strjoin_free_first(game->map[i], " ");
			if (!temp)
				ft_error_and_exit("ft_strjoin() failed\n");
			game->map[i] = temp;
		}
		i++;
	}
	game->map_cols = max_len;
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
		ft_error_and_exit("Malloc() failed to allocate 2d array\n");
	ret[size] = NULL;
	while (i < size)
	{
		ret[i] = temp_map->line;
		i++;
		temp_map = temp_map->next;
	}
	game->map = ret;
	game->map_rows = size;
	adjust_string_lengths(game);
}

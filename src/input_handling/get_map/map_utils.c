/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:56:33 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/18 15:17:21 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map	*ft_lstnew_map(void *content)
{
	t_map	*ptr;

	ptr = (t_map *)malloc(sizeof(t_map));
	if (ptr == (NULL))
		ft_error_and_exit("Malloc failure\n");
	ptr->line = content;
	ptr->next = (NULL);
	return (ptr);
}

void	ft_mapadd_back(t_map **lst, t_map *new_node)
{
	t_map	*temp;

	if (new_node != (NULL) && lst != (NULL))
	{
		if (*lst != (NULL))
		{
			temp = *lst;
			while (temp->next != (NULL))
				temp = temp->next;
			temp->next = new_node;
		}
		else
			*lst = new_node;
	}
}

int	map_lstsize(t_map *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst != (NULL))
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

void	set_player(t_player *player, int x, int y, char dir)
{
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	player->dir.x = 0;
	player->dir.y = 0;
	if (dir == 'N')
		player->dir.y = -1;
	if (dir == 'E')
		player->dir.x = 1;
	if (dir == 'S')
		player->dir.y = 1;
	if (dir == 'W')
		player->dir.x = -1;
}

/*frees the t_map linked list nodes but does NOT free the string stored inside
because those pointers go straight into the 2d array*/
void	free_map(t_map *map)
{
	t_map	*temp;

	while (map)
	{
		temp = map;
		map = map->next;
		free(temp);
	}
}

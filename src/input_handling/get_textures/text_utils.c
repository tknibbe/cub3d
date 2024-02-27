/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:44:05 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/27 18:05:14 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

#define GET 2

void	not_all_textures_set(t_textures *t)
{
	if ((!t->north || !t->east || !t->south \
		|| !t->west) || count_rgb(GET))
		ft_error_and_exit("Error, not all textures are set\n");
}

void	check_double_texture(t_textures *text, int cat)
{
	if ((cat == NO && text->north) \
		|| (cat == EA && text->east)
		|| (cat == SO && text->south) \
		|| (cat == WE && text->west))
		ft_error_and_exit("Error, double texture found\n");
}

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
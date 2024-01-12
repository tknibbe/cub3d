/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:44:05 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/10 16:28:36 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	not_all_textures_set(t_textures *t)
{
	if ((!t->north || !t->east || !t->south \
		|| !t->west) || (t->floor == -1 || t->ceiling == -1))
	{
		printf("not enough textures found(replace this message)\n");
		exit(1);
	}
}

void	check_double_texture(t_textures *text, int cat)
{
	if ((cat == NO && text->north) \
		|| (cat == EA && text->east)
		|| (cat == SO && text->south) \
		|| (cat == WE && text->west))
	{
		printf("double texture found (replace message)\n");
		exit(1);
	}
}

void	max_int_check_str(char *str)
{
	if (ft_strlen(str) > 10)
	{
		printf("number too big (replace)\n");
		exit(1);
	}
	// if (ft_strlen )
}

int	valid_rgb_value(char *s)
{
	int i;

	i = 0;
	if (ft_strlen(s) > 3)
	{
		printf("invalid rgb value! replace this error\n");
		exit(1);
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i])) // && s[i] != '-')
		{
			printf("invalid char found in rgb value! replace this error\n");
			exit(1);
		}
		i++;
	}
	if (!ft_isdigit(s[i-1]))
		exit(1);
	return (EXIT_SUCCESS);
}
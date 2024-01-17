/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:44:05 by tknibbe           #+#    #+#             */
/*   Updated: 2024/01/17 16:24:18 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

#define SETF 0
#define SETC 1
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

int	valid_rgb_value(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) > 3)
		ft_error_and_exit("Error, invalid RGB value (individual value is longer than 3 chars)\n");
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			ft_error_and_exit("Error, invalid character found inside RGB value\n");
		i++;
	}
	if (!ft_isdigit(s[i - 1]))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	count_rgb(int state)
{
	static int	f;
	static int	c;

	if (state == SETF)
		f++;
	else if (state == SETC)
		c++;
	if (f == 1 && c == 1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	calculate_rgb(char **nums)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	num;

	i = 0;
	while (nums[i])
	{
		nums[i] = ft_strdel(nums[i], " ");
		valid_rgb_value(nums[i]);
		nums[i] = ft_strdel(nums[i], " ");
		num = ft_atoi(nums[i]);
		if (num > 255 || num < 0)
			break ;
		i++;
	}
	if (i != 3)
		ft_error_and_exit("RGB value incorrect\n");
	r = ft_atoi(nums[0]);
	g = ft_atoi(nums[1]);
	b = ft_atoi(nums[2]);
	return ((r << 24) | (g << 16) | (b << 8) | TRANSPARANCY);
}
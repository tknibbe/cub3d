/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:13:50 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/07 16:21:22 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

#define SETF 0
#define SETC 1
#define GET 2

int	check_f_and_c(t_textures *text, char *line)
{
	if (!ft_strncmp(line, "F", 1))
	{
		text->floor = get_rgb(line);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		text->ceiling = get_rgb(line);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	get_rgb(char *line)
{
	int		i;
	char	**nums;
	int		ret;

	i = 0;
	if (line[i] == 'F')
		count_rgb(SETF);
	else
		count_rgb(SETC);
	i++;
	while (ft_isspace(line[i]))
		i++;
	nums = ft_split(&line[i], ',');
	if (!nums)
		ft_error_and_exit("Malloc() failed in ft_split()\n");
	ret = calculate_rgb(nums);
	ft_free_array(nums);
	return (ret);
}

int	valid_rgb_value(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) > 3)
		ft_error_and_exit("Error, invalid RGB value\n");
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			ft_error_and_exit("Error, invalid character inside RGB value\n");
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

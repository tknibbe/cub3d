/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_randomized_sprites.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/15 11:59:54 by jmolenaa      #+#    #+#                 */
/*   Updated: 2024/02/15 11:59:54 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <time.h>

#define SPRITE_DIV 4

static bool	already_rolled(int rolled_number, int *selected_numbers, int i)
{
	while (i > 0)
	{
		if (rolled_number == selected_numbers[i])
			return (true);
		i--;
	}
	return (false);
}

// chooses empty_spots_nr / SPRITE_DIV random spots to put sprites in
// randomises if it's a lamp or a cheerleader
// also checks if the spot we have has already been rolled, so we don't
// overlap sprites
void	randomise_sprites_positions(t_coords *empty_spots, int empty_spots_nr)
{
	int	i;
	int	*selected_numbers;
	int	random_number;

	srand(time(NULL));
	selected_numbers = ft_calloc(empty_spots_nr / SPRITE_DIV, sizeof(int));
	if (selected_numbers == NULL)
		ft_error_and_exit("Malloc failure\n");
	i = 0;
	while (i < empty_spots_nr / SPRITE_DIV)
	{
		random_number = rand() % empty_spots_nr;
		if (already_rolled(random_number, selected_numbers, i))
			continue ;
		empty_spots[random_number].type = (rand() % 2) + 1;
		selected_numbers[i] = random_number;
		i++;
	}
	free(selected_numbers);
}

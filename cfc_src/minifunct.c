/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifunct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:08:30 by tboissel          #+#    #+#             */
/*   Updated: 2019/01/31 13:09:36 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "championship.h"

int		ft_exit(void)
{
	exit(0);
	return (0);
}

int		rand_a_b(int a, int b)
{
	return (rand() % (b - a) + a);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	randomize_draw(char **names)
{
	int	i;
	int	first;
	int	second;

	i = 0;
	while (i++ < 30)
	{
		first = rand_a_b(0, 7);
		second = rand_a_b(0, 7);
		ft_swap(&names[first], &names[second]);
	}
}

void	get_names(t_fight *club, char **av)
{
	int	i;

	if (!(club->names = malloc(8 * sizeof(char *))))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < 8)
	{
		if (!(club->names[i] = ft_strdup(av[i + 1])))
			exit(EXIT_FAILURE);
	}
	randomize_draw(club->names);
}

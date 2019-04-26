/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:36:11 by tboissel          #+#    #+#             */
/*   Updated: 2019/02/01 14:14:28 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "championship.h"

void	create_background(t_fight *club)
{
	int	i;
	int	width;
	int height;

	width = 0;
	height = 0;
	i = -1;
	club->mlx->img.img_ptr = mlx_xpm_file_to_image(club->mlx->m_ptr,
	"img/Background_42.xpm", &width, &height);
	club->mlx->img.data = (int *)mlx_get_data_addr(club->mlx->img.img_ptr,
	&club->mlx->img.bpp, &club->mlx->img.size_l, &club->mlx->img.endian);
	draw_all_rect(club);
	draw_lines(club);
}

t_list	*init_list(t_fight *club)
{
	int		i;
	t_list	*players;
	t_list	*new;

	i = 0;
	if (!(players = ft_lstnew(ft_strdup(club->names[0]), 0)))
		exit(EXIT_FAILURE);
	while (++i < 8)
	{
		if (!(new = ft_lstnew(ft_strdup(club->names[i]), 0)))
			exit(EXIT_FAILURE);
		ft_lstpush(&players, new);
	}
	return (players);
}

void	write_winner_name(char *path, t_fight *club, int gn)
{
	char	*name;

	name = fc_name(path, 25);
	if (gn == 4)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 1265 + 5
		* (28 - ft_strlen(name)), 998, 0xFFFFFF, name);
	else if (gn == 3)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 1265 + 5
		* (28 - ft_strlen(name)), 280, 0xFFFFFF, name);
	else if (gn == 2)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 465 + 5
		* (28 - ft_strlen(name)), 998, 0xFFFFFF, name);
	else if (gn == 1)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 465 + 5
		* (28 - ft_strlen(name)), 280, 0xFFFFFF, name);
	else if (gn == 6)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 1055 + 5
		* (28 - ft_strlen(name)), 639, 0xFFFFFF, name);
	else if (gn == 5)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 670 + 5
		* (28 - ft_strlen(name)), 639, 0xFFFFFF, name);
	else if (gn == 7)
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, 862 + 5
		* (28 - ft_strlen(name)), 440, 0xFFFFFF, name);
	free(name);
}

void	competition(t_list **players, t_fight *club, int game_nb)
{
	int		winner;
	char	*call;
	t_list	*tmp;

	if (!(call = ft_strnew(16 + 3 * club->visu + ft_strlen((*players)->content)
		+ ft_strlen((*players)->next->content))))
		exit(0);
	ft_strcpy(call, (club->visu ? "./corewar -c -v " : "./corewar -c "));
	ft_strcat(call, (*players)->content);
	ft_strcat(call, " ");
	ft_strcat(call, (*players)->next->content);
	winner = system(call);
	if (winner == 65280)
		exit(EXIT_FAILURE);
	free(call);
	game_nb++;
	write_winner_name((!winner ? (*players)->content
		: (*players)->next->content), club, game_nb);
	tmp = (*players)->next;
	ft_lstremove(&club->begin, (!winner ? (*players)->next : *players));
	*players = !winner ? (*players)->next : tmp->next;
	if (!(*players) || !(*players)->next)
		*players = club->begin;
}

int		main(int ac, char **av)
{
	t_fight *club;

	if (ac != 9 && !(ac == 10 && av[1][0] == '-' && av[1][1] == 'v'))
	{
		write(1, "You need to provide 8 champions for the tournament\n", 51);
		exit(0);
	}
	if (!(club = ft_memalloc(sizeof(t_fight))))
		return (0);
	if (ac == 10 && av[1][0] == '-' && av[1][1] == 'v')
	{
		av++;
		club->visu = 1;
	}
	get_names(club, av);
	club->players = init_list(club);
	club->begin = club->players;
	init_mlx(club);
	create_background(club);
	ft_full_image(club);
	mlx_hook(club->mlx->w, 17, 0, &ft_exit, 0);
	mlx_key_hook(club->mlx->w, key_events, club);
	mlx_loop(club->mlx->m_ptr);
}

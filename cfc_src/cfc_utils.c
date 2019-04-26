/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:07:41 by tboissel          #+#    #+#             */
/*   Updated: 2019/01/31 13:02:10 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "championship.h"

int		ft_full_image(t_fight *club)
{
	void	*trophy;
	int		width;
	int		height;

	height = 0;
	width = 0;
	mlx_put_image_to_window(club->mlx->m_ptr, club->mlx->w,
	club->mlx->img.img_ptr, 0, 0);
	trophy = mlx_xpm_file_to_image(club->mlx->m_ptr, "img/Trophy.xpm",
	&width, &height);
	mlx_put_image_to_window(club->mlx->m_ptr, club->mlx->w, trophy, 850, 150);
	put_names(club);
	return (0);
}

void	put_names(t_fight *club)
{
	int		i;
	char	*name;
	t_coord	*deb;

	if (!(deb = ft_memalloc(sizeof(t_coord))))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < 8)
	{
		name = fc_name(club->names[i], 25);
		if (name == NULL)
			exit(EXIT_FAILURE);
		get_coord_champ(deb, i, name);
		mlx_string_put(club->mlx->m_ptr, club->mlx->w, deb->x, deb->y,
		0xFFFFFF, name);
		free(name);
	}
	free(deb);
}

void	get_coord_champ(t_coord *deb, int i, char *name)
{
	if (i < 4)
		deb->x = 62 + (28 - ft_strlen(name)) * 5;
	else
		deb->x = 1657 + (28 - ft_strlen(name)) * 5;
	if (i == 0 || i == 4)
		deb->y = 128;
	else if (i == 1 || i == 5)
		deb->y = 428;
	else if (i == 2 || i == 6)
		deb->y = 848;
	else
		deb->y = 1148;
}

int		key_events(int key, t_fight *club)
{
	static char rd = -1;

	if (key == ESC)
		exit(0);
	else if (key != CTRL && ++rd < 7)
		competition(&club->players, club, rd);
	return (0);
}

void	init_mlx(t_fight *club)
{
	if (!(club->mlx = ft_memalloc(sizeof(t_minilibx))))
		exit(EXIT_FAILURE);
	club->mlx->w_height = 1300;
	club->mlx->w_width = 2000;
	club->mlx->m_ptr = mlx_init();
	club->mlx->w = mlx_new_window(club->mlx->m_ptr, club->mlx->w_width,
	club->mlx->w_height, "Corewar Fight Club");
	club->mlx->img.img_ptr = mlx_new_image(club->mlx->m_ptr,
	club->mlx->w_width, club->mlx->w_height);
	club->mlx->img.data = (int *)mlx_get_data_addr(club->mlx->img.img_ptr,
	&club->mlx->img.bpp, &club->mlx->img.size_l, &club->mlx->img.endian);
}

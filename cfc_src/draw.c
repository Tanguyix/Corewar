/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:05:52 by tboissel          #+#    #+#             */
/*   Updated: 2019/01/31 13:35:58 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "championship.h"

void	draw_rectangle(t_fight *club, int x, int y, int color)
{
	int		i;
	int		j;
	t_coord point;

	point.x = x;
	point.y = y;
	i = -1;
	while (++i < 300)
	{
		j = -1;
		while (++j < 120)
			club->mlx->img.data[point.x + i + (point.y + j)
			* club->mlx->w_width] = color;
	}
}

void	draw_horizontal_line(int x1, int x2, int y, t_fight *club)
{
	int		i;
	int		j;
	t_coord point;

	point.x = x1;
	point.y = y;
	i = -1;
	while (x1 + ++i < x2)
	{
		j = -5;
		while (++j <= 10)
			club->mlx->img.data[point.x + i + (point.y + j)
			* club->mlx->w_width] = club->color;
	}
}

void	draw_vertical_line(int y1, int y2, int x, t_fight *club)
{
	int		i;
	int		j;
	t_coord point;

	point.x = x;
	point.y = y1 - 4;
	i = -5;
	while (++i <= 5)
	{
		j = -1;
		while (++j + point.y < y2 + 11)
			club->mlx->img.data[point.x + i + (point.y + j)
			* club->mlx->w_width] = club->color;
	}
}

void	draw_lines(t_fight *club)
{
	club->color = 0x989898;
	draw_horizontal_line(950, 1050, 645, club);
	draw_horizontal_line(350, 390, 135, club);
	draw_horizontal_line(350, 390, 435, club);
	draw_horizontal_line(350, 390, 1155, club);
	draw_horizontal_line(350, 390, 855, club);
	draw_horizontal_line(1610, 1650, 135, club);
	draw_horizontal_line(1610, 1650, 435, club);
	draw_horizontal_line(1610, 1650, 1155, club);
	draw_horizontal_line(1610, 1650, 855, club);
	draw_vertical_line(135, 435, 390, club);
	draw_vertical_line(855, 1155, 390, club);
	draw_vertical_line(135, 435, 1610, club);
	draw_vertical_line(855, 1155, 1610, club);
	draw_horizontal_line(390, 450, 285, club);
	draw_horizontal_line(390, 450, 1005, club);
	draw_horizontal_line(1550, 1610, 285, club);
	draw_horizontal_line(1550, 1610, 1005, club);
	draw_vertical_line(355, 939, 595, club);
	draw_vertical_line(355, 939, 1410, club);
	draw_horizontal_line(595, 650, 645, club);
	draw_horizontal_line(950, 1050, 645, club);
	draw_horizontal_line(1350, 1410, 645, club);
	draw_vertical_line(514, 635, 995, club);
}

void	draw_all_rect(t_fight *club)
{
	draw_rectangle(club, 50, 80, 0);
	draw_rectangle(club, 50, 380, 0);
	draw_rectangle(club, 50, 1100, 0);
	draw_rectangle(club, 50, 800, 0);
	draw_rectangle(club, 1650, 80, 0);
	draw_rectangle(club, 1650, 380, 0);
	draw_rectangle(club, 1650, 1100, 0);
	draw_rectangle(club, 1650, 800, 0);
	draw_rectangle(club, 450, 230, 0);
	draw_rectangle(club, 450, 950, 0);
	draw_rectangle(club, 1250, 230, 0);
	draw_rectangle(club, 1250, 950, 0);
	draw_rectangle(club, 650, 590, 0);
	draw_rectangle(club, 1050, 590, 0);
	draw_rectangle(club, 850, 390, 0xBE9A3B);
}

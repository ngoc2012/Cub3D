/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/02 15:57:20 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_hero(int yp, int xp, int *addr)
{
	int	i;
	int	j;

	yp -= 3;
	xp -= 5;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			addr[yp * WIDTH + (xp + j)] = create_trgb(1, 255, 0, 0);
			j++;
		}
		yp += 1;
		i++;
	}
}

void	wall(int *addr, int p, int k, int count)
{
	int	v;
	int	i;
	int	h;
	int	l;

	l = (((WIDTH / 4) / 9));
	h = (((HEIGHT / 4) / 9));
	i = 1;
	while (i < h)
	{
		v = 1;
		while (v < l)
		{
			if (count == 1)
				addr[(i + (p * h)) * WIDTH + (v + (k * l))] = create_trgb(1,
						0, 255, 255);
			if (count == 0)
				addr[(i + (p * h)) * WIDTH + (v + (k * l))] = create_trgb(1,
						255, 255, 255);
			v++;
		}
		i++;
	}
}

void	draw_hero_and_wall(t_game *g, int l, int h, int *addr)
{
	int		i;
	int		j;
	int		k;
	int		p;

	i = g->pos.y - 4;
	p = 0;
	while (i <= g->pos.y + 4)
	{
		k = 0;
		j = g->pos.x - 4;
		while (j <= g->pos.x + 4)
		{
			if (i >= 0 && i < g->map.h && j >= 0 && j < g->map.l
				&& g->map.v[i][j] == B_WALL)
				wall(addr, p, k, 0);
			if (i >= 0 && i < g->map.h && j >= 0 && j < g->map.l
				&& g->map.v[i][j] == B_DOOR)
				wall(addr, p, k, 1);
			k++;
			j++;
		}
		i++;
		p++;
	}
	draw_hero(h / 2, l / 2, addr);
}

draw_life(int *addr, int l)
{
	int	i;
	int	j;

	i = 1;
	while (i < 25)
	{
		j = 6;
		while (j < l)
		{
			addr[(HEIGHT - 30 + i) * WIDTH + (WIDTH - j)] = create_trgb(1, 255, 0, 0);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_game *g)
{
	int	*addr;

	addr = (int *)g->mlx.addr;
	draw_hero_and_wall(g, WIDTH / 4, HEIGHT / 4, addr);
	draw_life(addr, WIDTH / 3);
}

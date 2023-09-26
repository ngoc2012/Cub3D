/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/09/26 10:48:13 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	carrer_perso(int yp, int xp, int *addr)
{
	int	i;
	int	j;

	yp -= 2;
	xp -= 2;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			addr[yp * WIDTH + (xp + j)] = create_trgb(1, 255, 0, 0);
			j++;
		}
		yp += 1;
		i++;
	}
}

void	wall(int *addr, int p, int k)
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
			addr[(i + (k * h)) * WIDTH + (v + (p * l))] = create_trgb(1, 255, 255, 255);
			v++;
		}
		i++;
	}
}

void	draw_hero(t_game *g, int l, int h)
{
	int		*addr;
	int		i;
	int		j;
	int		k;
	int		p;

	addr = (int *)g->mlx.addr;
	carrer_perso(h / 2, l / 2, addr);
	j = g->pos.y - 4;
	p = 0;
	while (j <= g->pos.y + 4)
	{
		k = 0;
		i = g->pos.x - 4;
		while (i <= g->pos.x + 4)
		{
			if (i >= 0 && i < g->map.h && j >= 0 && j < g->map.l
				&& g->map.v[i][j] == B_WALL)
				wall(addr, p, k);
			k++;
			i++;
		}
		j++;
		p++;
	}
}

void	draw_box(int h, int l, int *addr, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j <= h)
	{
		i = 0;
		while (i < l)
		{
			if (count == 1)
				addr[j * WIDTH + i] = create_trgb(1, 255, 0, 255);
			else
				addr[i * WIDTH + j] = create_trgb(1, 255, 0, 255);
			i++;
		}
		j += (h / 9);
	}
}

void	draw_square(t_game *g, int x, int y, int l, int h)
{
	int	xp;
	int	yp;
	int	*addr;

	addr = (int *)g->mlx.addr;
	draw_box(h, l, addr, 1);
	draw_box(l, h, addr, 0);
	draw_hero(g, l, h);
}

void	draw_mini_map(t_game *g)
{
	int	xmap;
	int	ymap;

	xmap = WIDTH / 4;
	ymap = HEIGHT / 4;
	draw_square(g, 0, 0, xmap, ymap);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/05 15:48:59 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void	draw_wall_map(t_game *g, int *addr, int i, int j)
{
	int		k;
	int		p;

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
}

void	draw_life(int *addr, int l)
{
	int	i;
	int	j;
	int	count;
	int	n;

	count = 0;
	n = 0;
	while (count < 3)
	{
		i = 1;
		while (i < 25)
		{
			j = 6;
			while (j < 20)
			{
				addr[(HEIGHT - 30 + i) * WIDTH + (WIDTH - j - n)]
					= create_trgb(255, 255, 0, 0);
				j++;
			}
			i++;
		}
		n += 20;
		count++;
	}
}

void	draw_mini_map(t_game *g)
{
	int	*addr;

	addr = (int *)g->mlx.addr;
	draw_wall_map(g, addr, g->pos.y - 4, g->pos.x - 4);
	draw_hero_map((HEIGHT / 4) / 2, (WIDTH / 4) / 2, addr);
	draw_life(addr, WIDTH / 3);
}

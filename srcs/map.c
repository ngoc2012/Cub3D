/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/26 10:10:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	free_map(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->h)
		free(m->v[i]);
	free(m->v);
}

static void	get_position(t_game *g, int i, int j, char c)
{
	if (c == '0')
		g->map.v[j][i] = B_GROUND;
	else if (c == '1')
		g->map.v[j][i] = B_WALL;
	else if (c == '2')
	{
		g->map.v[j][i] = B_SPRITE;
		g->map.v[j][i] = B_GROUND;
	}
	else if (c == '3')
		g->map.v[j][i] = B_D3;
	else if (c == '4')
		g->map.v[j][i] = B_D4;
	else if (c == '5')
		g->map.v[j][i] = B_D5;
	else if (c == '6')
		g->map.v[j][i] = B_D6;
	else if (c == 'X')
		g->map.v[j][i] = B_DOOR;
	else if (c == ' ')
		g->map.v[j][i] = B_EMPTY;
	else if (ft_strchr("NSWE", c))
	{
		g->map.v[j][i] = B_GROUND;
		g->pos.x = i;
		g->pos.y = j;
		printf("map x= %d, y = %d\n", g->pos.x, g->pos.y);
		g->pos.px = i * BOX_SIZE + BOX_SIZE / 2;
		g->pos.py = j * BOX_SIZE + BOX_SIZE / 2;
		if (c == 'N')
			g->pos.rot = 90 / ROT_STEP;
		else if (c == 'S')
			g->pos.rot = 270 / ROT_STEP;
		else if (c == 'W')
			g->pos.rot = 180 / ROT_STEP;
		else if (c == 'E')
			g->pos.rot = 0;
	}
}

int	check_map(char *s)
{
	while (*s)
		if (!ft_strchr(MAP_CHAR, *(s++)))
			return (0);
	return (1);
}

int	get_map(t_game *g, char *fn)
{
	int	fd;
	char	*s;
	int	i;
	int	j;

	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd);
	while (s)
	{
		if (check_map(s))
		{
			g->map.h++;
			if ((int) ft_strlen(s) - 1> g->map.l)
				g->map.l = (int) ft_strlen(s) - 1;
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	g->map.ph = g->map.h * BOX_SIZE;
	g->map.pl = g->map.l * BOX_SIZE;
	g->map.v = malloc(sizeof(enum e_map *) * g->map.h);
	fd = open(fn, O_RDONLY);
	j = -1;
	s = get_next_line(fd);
	while (s)
	{
		if (check_map(s))
		{
			g->map.v[++j] = malloc(sizeof(enum e_map) * g->map.l);
			i = 0;
			while (i < g->map.l)
				g->map.v[j][i++] = B_EMPTY;
			i = -1;
			while (s[++i])
				get_position(g, i, j, s[i]);
			while (i++ < g->map.l)
				g->map.v[j][i++] = B_EMPTY;
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	if (g->map.h < 5 || g->map.l < 5)
		end_game(g, 1, "Invalid map");
	return (1);
}

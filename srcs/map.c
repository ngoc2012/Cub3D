/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/19 12:21:29 by minh-ngu         ###   ########.fr       */
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
	if (c == '1')
		g->map.v[j][i] = 1;
	else if (c == '2')
		g->map.v[j][i] = 2;
	else if (c == '3')
		g->map.v[j][i] = 3;
	else if (c == '4')
		g->map.v[j][i] = 4;
	else if (c == '5')
		g->map.v[j][i] = 5;
	else if (c == '6')
		g->map.v[j][i] = 6;
	else if (c == '7')
		g->map.v[j][i] = 7;
	else if (c == ' ')
		g->map.v[j][i] = 1;
	else if (ft_strchr("NSWE", c))
	{
		g->pos.x = j;
		g->pos.y = i;
		g->pos.px = j * BOX_SIZE + BOX_SIZE / 2;
		g->pos.py = i * BOX_SIZE + BOX_SIZE / 2;
		if (c == 'N')
			g->pos.alpha = 90;
		else if (c == 'S')
			g->pos.alpha = -90;
		else if (c == 'W')
			g->pos.alpha = 180;
		else if (c == 'E')
			g->pos.alpha = 0;
	}
}

void	get_map(t_game *g, char *fn)
{
	int	fd;
	char	*s;
	int	i;
	int	j;

	fd = open(fn, O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		g->map.h++;
		if ((int) ft_strlen(s) > g->map.l)
			g->map.l = (int) ft_strlen(s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	g->map.v = malloc(sizeof(int *) * g->map.h);
	fd = open(fn, O_RDONLY);
	j = -1;
	s = get_next_line(fd);
	while (s)
	{
		g->map.v[++j] = malloc(sizeof(int) * g->map.l);
		i = 0;
		while (i < g->map.l)
			g->map.v[j][i++] = 0;
		i = -1;
		while (s[++i])
			get_position(g, i, j, s[i]);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	if (g->map.h < 5 || g->map.l < 5)
		end_game(g, 1, "Invalid map");
}

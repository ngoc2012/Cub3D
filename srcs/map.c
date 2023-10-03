/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/03 15:56:06 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	free_map(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->h)
		if (m->v[i])
			free(m->v[i]);
	free(m->v);
}

void	add_sprite(double px, double py, t_game *g)
{
	int		i;
	t_sprite	*new;

	g->n_sprites++;
	new = malloc(sizeof(t_sprite) * g->n_sprites);
	i = 0;
	while (i < g->n_sprites - 1)
	{
		new[i].px = g->sprites[i].px;
		new[i].py = g->sprites[i].py;
		i++;
	}
	new[i].px = px;
	new[i].py = py;
	free(g->sprites);
	g->sprites = new;
}

static void	get_position(t_game *g, int i, int j, char c)
{
	if (c == '0')
		g->map.v[j][i] = B_GROUND;
	else if (c == '1')
		g->map.v[j][i] = B_WALL;
	else if (c == '2')
	{
		add_sprite(i * BOX_SIZE + BOX_SIZE / 2, j * BOX_SIZE + BOX_SIZE / 2, g);
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
	char	*s0;

	s0 = s;
	while (ft_strchr(" 	\n", *s0))
		s0++;
	if (!*s0)
		return (0);
	while (*s)
		if (!ft_strchr(MAP_CHAR, *(s++)))
			return (0);
	return (1);
}

int	get_map(t_game *g, char *fn)
{
	int	count_perso;
	int	fd;
	char	*s;
	int	i;
	int	j;
	int	in_map;

	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd);
	while (s)
	{
		if (check_map(s))
		{
			g->map.h++;
			if ((int) ft_strlen(s) - 1 > g->map.l)
				g->map.l = (int) ft_strlen(s) - 1;
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	g->map.ph = g->map.h * BOX_SIZE;
	g->map.pl = g->map.l * BOX_SIZE;
	g->map.v = malloc(sizeof(enum e_map *) * g->map.h);
	i = -1;
	while (++i < g->map.h)
		g->map.v[i] = 0;
	fd = open(fn, O_RDONLY);
	j = -1;
	in_map = 0;
	s = get_next_line(fd);
	count_perso = 0;
	while (s)
	{
		if (check_map(s))
		{
			in_map = 1;
			g->map.v[++j] = malloc(sizeof(enum e_map) * g->map.l);
			i = 0;
			while (i < g->map.l)
				g->map.v[j][i++] = B_EMPTY;
			i = -1;
			while (s[++i])
			{
				if (s[i] == 'N' || s[i] == 'W' || s[i] == 'E' || s[i] == 'S')
					count_perso++;
				get_position(g, i, j, s[i]);
			}
			while (i++ < g->map.l)
				g->map.v[j][i++] = B_EMPTY;
		}
		else if (in_map)
		{
			free(s);
			close(fd);
			end_game(g, 1, "Invalid map\n");
		}
		free(s);
		s = get_next_line(fd);
	}
	if (count_perso == 0 || count_perso > 1)
		end_game(g, 1, "Invalid map\n");
	close(fd);
	if (g->map.h < 5 || g->map.l < 5)
		end_game(g, 1, "Invalid map\n");
	return (1);
}

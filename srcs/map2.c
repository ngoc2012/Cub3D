/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/11 17:09:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_position(t_game *g, int i, int j, char c)
{
	if (c == '0')
		g->map.v[j][i] = b_ground;
	else if (c == '1')
		g->map.v[j][i] = b_wall;
	else if (c == '2')
	{
		add_sprite(i * BOX_SIZE + BOX_SIZE / 2,
			j * BOX_SIZE + BOX_SIZE / 2, b_sprite, g);
		g->map.v[j][i] = b_ground;
	}
	else if (c == '3')
	{
		add_sprite(i * BOX_SIZE + BOX_SIZE / 2,
			j * BOX_SIZE + BOX_SIZE / 2, b_d3, g);
		g->map.v[j][i] = b_ground;
	}
	get_pos1(i, j, c, g);
	get_pos2(i, j, c, g);
}

void	check_line(t_game *g, char *s, int j)
{
	int	i;

	i = 0;
	while (i < g->map.l)
		g->map.v[j][i++] = b_empty;
	i = -1;
	while (s[++i])
	{
		if (ft_strchr("NSWE", s[i]))
		{
			if (g->map.perso)
			{
				free(s);
				end_game(g, 1, "Invalid map 2\n");
			}
			g->map.perso = 1;
		}
		get_position(g, i, j, s[i]);
	}
}

void	for_check_map(t_game *g, char *fn)
{
	int		fd;
	int		j;
	char	*s;

	j = -1;
	g->map.in_map = 0;
	g->map.perso = 0;
	fd = open(fn, O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		if (check_map(s))
		{
			g->map.in_map = 1;
			g->map.v[++j] = malloc(sizeof(enum e_map) * g->map.l);
			check_line(g, s, j);
		}
		else if (g->map.in_map)
			finish(s, fd, g);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}

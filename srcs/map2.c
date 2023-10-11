/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/11 15:12:16 by nbechon          ###   ########.fr       */
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

void	for_check_map(t_game *g, char *fn, int count_perso)
{
	int		i;
	int		fd;
	char	*s;
	int		j;
	int		in_map;

	j = -1;
	in_map = 0;
	count_perso = 0;
	fd = open(fn, O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		if (check_map(s))
		{
			in_map = 1;
			g->map.v[++j] = malloc(sizeof(enum e_map) * g->map.l);
			i = 0;
			while (i < g->map.l)
				g->map.v[j][i++] = b_empty;
			i = -1;
			while (s[++i])
			{
				if (s[i] == 'N' || s[i] == 'W' || s[i] == 'E' || s[i] == 'S')
					count_perso++;
				get_position(g, i, j, s[i]);
			}
		}
		else if (in_map)
			finish(s, fd, g);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	if (count_perso == 0 || count_perso > 1)
		end_game(g, 1, "Invalid map 2\n");
}

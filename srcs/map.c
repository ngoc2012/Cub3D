/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 14:19:03 by nbechon          ###   ########.fr       */
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
		{
			free(s);
			close(fd);
			end_game(g, 1, "Invalid map 1\n");
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	if (count_perso == 0 || count_perso > 1)
		end_game(g, 1, "Invalid map 2\n");
}

int	get_map(t_game *g, char *fn)
{
	int		fd;
	char	*s;
	int		i;

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
	if (g->map.h < 3 || g->map.l < 3)
		end_game(g, 1, "Invalid map 3\n");
	init_boxsize(g);
	for_check_map(g, fn, 0);
	verif_wall(g);
	return (1);
}

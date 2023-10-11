/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/11 14:52:06 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	finish(char *s, int fd, t_game *g)
{
	free(s);
	close(fd);
	end_game(g, 1, "Invalid map 1\n");
}

void	call(t_game *g, char *fn)
{
	init_boxsize(g);
	for_check_map(g, fn, 0);
	verif_wall(g);
}

int	get_map(t_game *g, char *fn)
{
	int		fd;
	char	*s;

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
	call(g, fn);
	return (1);
}

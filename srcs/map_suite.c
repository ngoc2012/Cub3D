/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_suite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 11:01:38 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_map *m)
{
	int	i;

	if (!m->v)
		return ;
	i = -1;
	while (++i < m->h)
		if (m->v[i])
			free(m->v[i]);
	free(m->v);
}

void	add_sprite(float px, double py, enum e_map type, t_game *g)
{
	int			i;
	t_sprite	*new;

	g->n_sprites++;
	new = malloc(sizeof(t_sprite) * g->n_sprites);
	i = 0;
	while (i < g->n_sprites - 1)
	{
		new[i].type = g->sprites[i].type;
		new[i].px = g->sprites[i].px;
		new[i].py = g->sprites[i].py;
		new[i].health = g->sprites[i].health;
		new[i].i_tex = g->sprites[i].i_tex;
		new[i].state = g->sprites[i].state;
		i++;
	}
	new[i].type = type;
	new[i].px = px;
	new[i].py = py;
	new[i].health = HEALTH_SPRITE;
	new[i].i_tex = rand() % (SPRITE_STATE * 3);
	new[i].state = s_normal;
	free(g->sprites);
	g->sprites = new;
}

void	init_boxsize(t_game *g)
{
	int	i;

	g->map.ph = g->map.h * BOX_SIZE;
	g->map.pl = g->map.l * BOX_SIZE;
	g->map.v = malloc(sizeof(enum e_map *) * g->map.h);
	i = -1;
	while (++i < g->map.h)
		g->map.v[i] = 0;
}

void	get_pos2(int i, int j, char c, t_game *g)
{
	if (c == 'X')
		g->map.v[j][i] = b_door;
	else if (c == ' ')
		g->map.v[j][i] = b_empty;
	else if (ft_strchr("NSWE", c))
	{
		g->map.v[j][i] = b_ground;
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

void	get_pos1(int i, int j, char c, t_game *g)
{
	if (c == '4')
	{
		add_sprite(i * BOX_SIZE + BOX_SIZE / 2,
			j * BOX_SIZE + BOX_SIZE / 2, b_d4, g);
		g->map.v[j][i] = b_ground;
	}
	else if (c == '5')
	{
		add_sprite(i * BOX_SIZE + BOX_SIZE / 2,
			j * BOX_SIZE + BOX_SIZE / 2, b_d5, g);
		g->map.v[j][i] = b_ground;
	}
	else if (c == '6')
	{
		add_sprite(i * BOX_SIZE + BOX_SIZE / 2,
			j * BOX_SIZE + BOX_SIZE / 2, b_d6, g);
		g->map.v[j][i] = b_ground;
	}
}

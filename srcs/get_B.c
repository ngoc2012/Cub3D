/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_B.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:38:22 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 21:42:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_b2(t_game *g, int ix, float ai)
{
	if (g->pos.bx < 0 || g->pos.bx >= g->map.l
		|| g->pos.by < 0 || g->pos.by >= g->map.h)
	{
		g->pos.db = INFINI;
		return ;
	}
	if (g->map.v[g->pos.by][g->pos.bx] == b_door && ai > -90.0 && ai < 90.0)
	{
		g->pos.db = (g->pos.bpx - g->pos.px + BOX_SIZE / 2)
			/ g->cos_ai[ix][g->pos.rot];
		g->pos.bpy += g->pos.dpy / 2;
	}
	else if (g->map.v[g->pos.by][g->pos.bx] == b_door)
	{
		g->pos.db = (g->pos.bpx - g->pos.px - BOX_SIZE / 2)
			/ g->cos_ai[ix][g->pos.rot];
		g->pos.bpy += g->pos.dpy / 2;
	}
	else
		g->pos.db = (g->pos.bpx - g->pos.px)
			/ g->cos_ai[ix][g->pos.rot];
}

void	get_b1(t_game *g, int ix, float ai)
{
	int	door_coor;

	g->pos.bx = g->pos.bpx / BOX_SIZE;
	if (ai <= -90.0 || ai >= 90.0)
		g->pos.bx--;
	door_coor = (int)(g->pos.bpy + g->pos.dpy / 2
			- BOX_SIZE * (float) g->pos.by);
	while ((g->pos.bx >= 0 && g->pos.bx < g->map.l)
		&& (g->pos.by >= 0 && g->pos.by < g->map.h)
		&& ((g->map.v[g->pos.by][g->pos.bx] != b_wall
			&& g->map.v[g->pos.by][g->pos.bx] != b_door)
			|| (g->pos.by == g->opened_door_y && g->pos.bx == g->opened_door_x
			&& g->map.v[g->pos.by][g->pos.bx] == b_door
			&& door_coor < g->hidden_door)))
	{
		g->pos.bpx += g->pos.dpx;
		g->pos.bpy += g->pos.dpy;
		g->pos.by = g->pos.bpy / BOX_SIZE;
		if (ai > -90.0 && ai < 90.0)
			g->pos.bx = g->pos.bpx / BOX_SIZE;
		else
			g->pos.bx = g->pos.bpx / BOX_SIZE - 1;
		door_coor = (int)(g->pos.bpy + g->pos.dpy / 2
				- BOX_SIZE * (float) g->pos.by);
	}
}

void	get_b(t_game *g, int ix, float ai)
{
	if (ai > -90.0 && ai < 90.0)
	{
		g->pos.bpx = ((int)(g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		g->pos.dpx = BOX_SIZE;
	}
	else
	{
		g->pos.bpx = ((int)(g->pos.px / BOX_SIZE)) * BOX_SIZE;
		g->pos.dpx = -BOX_SIZE;
	}
	g->pos.bpy = g->pos.py + (g->pos.px - g->pos.bpx)
		* g->tan_ai[ix][g->pos.rot];
	g->pos.dpy = BOX_SIZE * g->tan_ai[ix][g->pos.rot];
	if (ai * g->pos.dpy > 0)
		g->pos.dpy = -g->pos.dpy;
	if (g->pos.bpy < 0 || g->pos.bpy >= g->map.ph)
	{
		g->pos.db = INFINI;
		return ;
	}
	g->pos.by = g->pos.bpy / BOX_SIZE;
	get_b1(g, ix, ai);
	get_b2(g, ix, ai);
}

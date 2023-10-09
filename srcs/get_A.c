/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_A.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:15:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 21:24:14 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_a1(t_game *g, int ix, float ai)
{
	int	door_coor;
	int	ax;
	int	ay;

	ax = g->pos.ax;
	ay = g->pos.ay;
	ax = g->pos.apx / BOX_SIZE;
	door_coor = (int)(g->pos.apx + g->pos.dpx / 2 - BOX_SIZE * (float) ax);
	while ((ax >= 0 && ax < g->map.l) && (ay >= 0 && ay < g->map.h)
		&& ((g->map.v[ay][ax] != b_wall && g->map.v[ay][ax] != b_door)
		|| (ay == g->opened_door_y && ax == g->opened_door_x
		&& g->map.v[ay][ax] == b_door && door_coor < g->hidden_door)))
	{
		g->pos.apx += g->pos.dpx;
		g->pos.apy += g->pos.dpy;
		ax = g->pos.apx / BOX_SIZE;
		if (ai > 0.0)
			ay = g->pos.apy / BOX_SIZE - 1;
		else
			ay = g->pos.apy / BOX_SIZE;
		door_coor = (int)(g->pos.apx + g->pos.dpx / 2 - BOX_SIZE * (float) ax);
	}
	g->pos.ax = ax;
	g->pos.ay = ay;
}

static void	get_a2(t_game *g, int ix, float ai)
{
	if (g->pos.ax < 0 || g->pos.ax >= g->map.l
		|| g->pos.ay < 0 || g->pos.ay >= g->map.h)
	{
		g->pos.da = INFINI;
		return ;
	}
	if (g->map.v[g->pos.ay][g->pos.ax] == b_door && ai > 0.0)
	{
		g->pos.da = (g->pos.py - g->pos.apy + BOX_SIZE / 2)
			/ g->sin_ai[ix][g->pos.rot];
		g->pos.apx += g->pos.dpx / 2;
	}
	else if (g->map.v[g->pos.ay][g->pos.ax] == b_door)
	{
		g->pos.da = (g->pos.py - g->pos.apy - BOX_SIZE / 2)
			/ g->sin_ai[ix][g->pos.rot];
		g->pos.apx += g->pos.dpx / 2;
	}
	else
		g->pos.da = (g->pos.py - g->pos.apy) / g->sin_ai[ix][g->pos.rot];
}

static void	get_a(t_game *g, int ix, float ai)
{
	g->pos.apy = ((int)(g->pos.py / BOX_SIZE)) * BOX_SIZE;
	g->pos.dpy = -BOX_SIZE;
	if (ai <= 0.0)
	{
		g->pos.apy += BOX_SIZE;
		g->pos.dpy = BOX_SIZE;
	}
	g->pos.apx = g->pos.px + (g->pos.py - g->pos.apy)
		* g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
	g->pos.dpx = BOX_SIZE * g->cos_ai[ix][g->pos.rot]
		/ g->sin_ai[ix][g->pos.rot];
	if (ai < 0)
		g->pos.dpx = -g->pos.dpx;
	if (g->pos.apx < 0 || g->pos.apx >= g->map.pl)
	{
		g->pos.da = INFINI;
		return ;
	}
	g->pos.ay = g->pos.apy / BOX_SIZE;
	if (ai > 0.0)
		g->pos.ay--;
	get_a1(g, ix, ai);
	get_a2(g, ix, ai);
}

void	get_ab(t_game *g, int ix)
{
	float	ai;

	g->pos.da = 0.0;
	g->pos.db = 0.0;
	ai = g->ai[ix][g->pos.rot];
	if ((-g->tol_l < ai && ai < g->tol_l)
		|| (180.0 - g->tol_l < ai) || ai < -(180.0 - g->tol_l))
	{
		g->pos.da = INFINI;
		get_b(g, ix, ai);
	}
	else if ((90.0 - g->tol_h < ai && ai < 90.0 + g->tol_h)
		|| (-90.0 - g->tol_h < ai && ai < -90.0 + g->tol_h))
	{
		g->pos.db = INFINI;
		get_a(g, ix, ai);
	}
	else
	{
		get_a(g, ix, ai);
		get_b(g, ix, ai);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_A.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:27:15 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 10:14:42 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_a1(t_game *g, int ix, float ai)
{
	int	door_coor;
	int	ax;
	int	ay;

	ax = g->pos.Ax;
	ay = g->pos.Ay;
	ax = g->pos.Apx / BOX_SIZE;
	if (ai > 0.0)
		ay = g->pos.Apy / BOX_SIZE - 1;
	else
		ay = g->pos.Apy / BOX_SIZE;
	door_coor = (int)(g->pos.Apx + g->pos.dpx / 2 - BOX_SIZE * (float) ax);
	while ((ax >= 0 && ax < g->map.l) && (ay >= 0 && ay < g->map.h)
		&& ((g->map.v[ay][ax] != B_WALL && g->map.v[ay][ax] != B_DOOR)
		|| (ay == g->opened_door_y && ax == g->opened_door_x
		&& g->map.v[ay][ax] == B_DOOR && door_coor < g->hidden_door)))
	{
		g->pos.Apx += g->pos.dpx;
		g->pos.Apy += g->pos.dpy;
		ax = g->pos.Apx / BOX_SIZE;
		if (ai > 0.0)
			ay = g->pos.Apy / BOX_SIZE - 1;
		else
			ay = g->pos.Apy / BOX_SIZE;
		door_coor = (int)(g->pos.Apx + g->pos.dpx / 2 - BOX_SIZE * (float) ax);
	}
	g->pos.Ax = ax;
	g->pos.Ay = ay;
}

static void	get_a2(t_game *g, int ix, float ai)
{
	if (g->pos.Ax < 0 || g->pos.Ax >= g->map.l || g->pos.Ay < 0 || g->pos.Ay >= g->map.h)
	{
		g->pos.dA = INFINI;
		return ;
	}
	if (g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR && ai > 0.0)
	{
		g->pos.dA = (g->pos.py - g->pos.Apy + BOX_SIZE / 2) / g->sin_ai[ix][g->pos.rot];
		g->pos.Apx += g->pos.dpx / 2;
	}
	else if (g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR)
	{
		g->pos.dA = (g->pos.py - g->pos.Apy - BOX_SIZE / 2) / g->sin_ai[ix][g->pos.rot];
		g->pos.Apx += g->pos.dpx / 2;
	}
	else
		g->pos.dA = (g->pos.py - g->pos.Apy) / g->sin_ai[ix][g->pos.rot];
}

static void	get_a(t_game *g, int ix, float ai)
{
	if (ai > 0.0)
	{
		g->pos.Apy = ((int)(g->pos.py / BOX_SIZE)) * BOX_SIZE;
		g->pos.dpy = -BOX_SIZE;
	}
	else
	{
		g->pos.Apy = ((int)(g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		g->pos.dpy = BOX_SIZE;
	}
	g->pos.Apx = g->pos.px + (g->pos.py - g->pos.Apy) * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
	g->pos.dpx = BOX_SIZE * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
	if (ai < 0)
		g->pos.dpx = -g->pos.dpx;
	if (g->pos.Apx < 0 || g->pos.Apx >= g->map.pl)
	{
		g->pos.dA = INFINI;
		return ;
	}
	get_a1(g, ix, ai);
	get_a2(g, ix, ai);
}

void	get_ab(t_game *g, int ix)
{
	float	ai;

	g->pos.dA = 0.0;
	g->pos.dB = 0.0;
	ai = g->ai[ix][g->pos.rot];
	if ((-g->tol_l < ai && ai < g->tol_l) ||
		(180.0 - g->tol_l < ai) || ai < -(180.0 - g->tol_l))
	{
		g->pos.dA = INFINI;
		get_b(g, ix, ai);
	}
	else if ((90.0 - g->tol_h < ai && ai < 90.0 + g->tol_h) ||
		(-90.0 - g->tol_h < ai && ai < -90.0 + g->tol_h))
	{
		g->pos.dB = INFINI;
		get_a(g, ix, ai);
	}
	else
	{
		get_a(g, ix, ai);
		get_b(g, ix, ai);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_B.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:30:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 10:07:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_b(t_game *g, int ix, float ai)
{
	int	Bx;
	int	By;
	float	Bpx;
	float	Bpy;
	float	dpx;
	float	dpy;
	int	door_coor;

	if (ai > -90.0 && ai < 90.0)
	{
		Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		dpx = BOX_SIZE;
	}
	else
	{
		Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE;
		dpx = -BOX_SIZE;
	}
	Bpy = g->pos.py + (g->pos.px - Bpx) * g->tan_ai[ix][g->pos.rot];
	dpy = BOX_SIZE * g->tan_ai[ix][g->pos.rot];
	if (ai * dpy > 0)
		dpy = -dpy;
	if (Bpy < 0 || Bpy >= g->map.ph)
	{
		g->pos.dB = INFINI;
		return ;
	}
	By = Bpy / BOX_SIZE;
	if (ai > -90.0 && ai < 90.0)
		Bx = Bpx / BOX_SIZE;
	else
		Bx = Bpx / BOX_SIZE - 1;
	door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
	while ((Bx >= 0 && Bx < g->map.l) && (By >= 0 && By < g->map.h) &&
			((g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
			 || (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == B_DOOR && door_coor < g->hidden_door)))
	{
		Bpx += dpx;
		Bpy += dpy;
		By = Bpy / BOX_SIZE;
		if (ai > -90.0 && ai < 90.0)
			Bx = Bpx / BOX_SIZE;
		else
			Bx = Bpx / BOX_SIZE - 1;
		door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
	}
	if (Bx < 0 || Bx >= g->map.l || By < 0 || By >= g->map.h)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (g->map.v[By][Bx] == B_DOOR && ai > -90.0 && ai < 90.0)
	{
		g->pos.dB = (Bpx - g->pos.px + BOX_SIZE / 2) / g->cos_ai[ix][g->pos.rot];
		Bpy += dpy / 2;
	}
	else if (g->map.v[By][Bx] == B_DOOR)
	{
		g->pos.dB = (Bpx - g->pos.px - BOX_SIZE / 2) / g->cos_ai[ix][g->pos.rot];
		Bpy += dpy / 2;
	}
	else
		g->pos.dB = (Bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
	g->pos.Bx = Bx;
	g->pos.By = By;
	g->pos.Bpy = Bpy;
}

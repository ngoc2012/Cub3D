/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/11 15:40:54 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_press_norm2(t_game *g, int keycode)
{
	if (keycode == XK_w)
		g->frames[fr_up] = 1;
	else if (keycode == XK_s)
		g->frames[fr_down] = 1;
	else if (keycode == XK_a)
		g->frames[fr_left] = 1;
	else if (keycode == XK_d)
		g->frames[fr_right] = 1;
}

float	norm(int keycode, t_game *g)
{
	float	dx;

	dx = (int)(TRANS_STEP * cos(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_w)
		dx = -dx;
	return (dx);
}

float	norm2(int keycode, t_game *g)
{
	float	dy;

	dy = (int)(TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_w)
		dy = -dy;
	return (dy);
}

float	norm3(int keycode, t_game *g)
{
	float	dx;

	dx = (int)(TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_d)
		dx = -dx;
	return (dx);
}

float	norm4(int keycode, t_game *g)
{
	float	dy;

	dy = (int)(TRANS_STEP * -cos(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_d)
		dy = -dy;
	return (dy);
}

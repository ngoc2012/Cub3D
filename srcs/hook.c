/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 10:21:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	key_hook(int keycode, t_game *g)
 {
 	if (keycode == XK_Up || keycode == XK_Down)
	{
		double	dx;
		double	dy;
		int	x;
		int	y;

		dx = (int) (TRANS_SPEED * cos(g->pos.alpha * PI / 180.0));
		dy = (int) (TRANS_SPEED * sin(g->pos.alpha * PI / 180.0));

		//printf("Key Up Down\n");
		if (keycode == XK_Up)
		{
			dx = -dx;
			dy = -dy;
		}
		x = (int) ((g->pos.px - dx) / BOX_SIZE);
		y = (int) ((g->pos.py + dy) / BOX_SIZE);
		if (x > 0 && y > 0 && x < g->map.l && y < g->map.h && !g->map.v[y][x])
		{
			g->pos.px -= dx;
			g->pos.py += dy;
			g->pos.x = x;
			g->pos.y = y;
			redraw(g);
			draw(g);
		}
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == XK_Right)
			g->pos.alpha -= ROT_SPEED;
		else
			g->pos.alpha += ROT_SPEED;
		g->pos.alpha = angle_convert(g->pos.alpha);
		redraw(g);
		draw(g);
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (0);
}

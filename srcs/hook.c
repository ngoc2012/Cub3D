/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/26 17:20:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	key_press(int keycode, t_game *g)
{
 	if (keycode == XK_Up || keycode == XK_Down)
	{
		double	dx;
		double	dy;
		int	x;
		int	y;

		dx = (int) (TRANS_STEP * cos(g->pos.rot * ROT_STEP * PI / 180.0));
		dy = (int) (TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));

		//printf("Key Up Down\n");
		if (keycode == XK_Up)
		{
			dx = -dx;
			dy = -dy;
		}
		x = (int) ((g->pos.px - dx) / BOX_SIZE);
		y = (int) ((g->pos.py + dy) / BOX_SIZE);
		if (((keycode == XK_Up && !g->frames[FR_UP]) ||
			(keycode == XK_Down && !g->frames[FR_DOWN])) &&
				(x > 0 && y > 0 && x < g->map.l && y < g->map.h && g->map.v[y][x] == B_GROUND &&
				g->map.v[y][(int) ((g->pos.px - dx + WALL_COLISION) / BOX_SIZE)] == B_GROUND &&
				g->map.v[y][(int) ((g->pos.px - dx - WALL_COLISION) / BOX_SIZE)] == B_GROUND &&
				g->map.v[(int) ((g->pos.py + dy + WALL_COLISION) / BOX_SIZE)][x] == B_GROUND &&
				g->map.v[(int) ((g->pos.py + dy - WALL_COLISION) / BOX_SIZE)][x] == B_GROUND))
		{
			g->pos.px -= dx;
			g->pos.py += dy;
			g->pos.x = x;
			g->pos.y = y;
			if (keycode == XK_Up)
				g->frames[FR_UP] = 1;
			else
				g->frames[FR_DOWN] = 1;
		}
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if ((keycode == XK_Right && !g->frames[FR_RIGHT]) ||
			(keycode == XK_Left && !g->frames[FR_LEFT]))
		{
			if (keycode == XK_Right)
				g->pos.rot--;
			else
				g->pos.rot++;
			if (g->pos.rot < 0)
				g->pos.rot += 360 / ROT_STEP;
			else if (g->pos.rot >= 360 / ROT_STEP)
				g->pos.rot = 0;
			if (keycode == XK_Right)
				g->frames[FR_RIGHT] = 1;
			else
				g->frames[FR_LEFT] = 1;
		}
	}
	return (1);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == XK_space && !g->frames[FR_DOOR])
	{
		if (g->map.v[g->pos.y - 1][g->pos.x] == B_DOOR)
		{
			g->opened_door_x = g->pos.x;
			g->opened_door_y = g->pos.y - 1;
			g->frames[FR_DOOR] = 1;
			g->opened = 1;
		}
		else if (g->map.v[g->pos.y + 1][g->pos.x] == B_DOOR)
		{
			g->opened_door_x = g->pos.x;
			g->opened_door_y = g->pos.y + 1;
			g->frames[FR_DOOR] = 1;
			g->opened = 1;
		}
		else if (g->map.v[g->pos.y][g->pos.x - 1] == B_DOOR)
		{
			g->opened_door_x = g->pos.x - 1;
			g->opened_door_y = g->pos.y;
			g->frames[FR_DOOR] = 1;
			g->opened = 1;
		}
		else if (g->map.v[g->pos.y][g->pos.x + 1] == B_DOOR)
		{
			g->opened_door_x = g->pos.x + 1;
			g->opened_door_y = g->pos.y;
			g->frames[FR_DOOR] = 1;
			g->opened = 1;
		}
	}
	if (keycode == XK_Control_L || keycode == XK_Control_R)
	{
		if (!g->frames[FR_GUN])
			g->frames[FR_GUN] = 1;
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (1);
}

int	mouse_hook(int button, int x, int y, t_game *g)
{
	if (button == 1)
	{
		double	alpha;
		alpha = atan(((double) x / SCALE - WIDTH / 2) / g->dpp) * 180.0 / PI; 
		g->pos.rot -= (int)  alpha / ROT_STEP;
		if (g->pos.rot < 0)
			g->pos.rot += 360 / ROT_STEP;
		else if (g->pos.rot >= 360 / ROT_STEP)
			g->pos.rot -= 360 / ROT_STEP;
	}
	return (1);
}

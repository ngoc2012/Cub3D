/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 20:56:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	key_press(int keycode, t_game *g)
{
 	if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d)
	{
		float	dx;
		float	dy;
		int	x;
		int	y;

		if (keycode == XK_w || keycode == XK_s)
		{
			dx = (int) (TRANS_STEP * cos(g->pos.rot * ROT_STEP * PI / 180.0));
			dy = (int) (TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));
			if (keycode == XK_w)
			{
				dx = -dx;
				dy = -dy;
			}
		}
		else
		{
			dx = (int) (TRANS_STEP *  sin(g->pos.rot * ROT_STEP * PI / 180.0));
			dy = (int) (TRANS_STEP * -cos(g->pos.rot * ROT_STEP * PI / 180.0));
			if (keycode == XK_d)
			{
				dx = -dx;
				dy = -dy;
			}
		}
		x = (int) ((g->pos.px - dx) / BOX_SIZE);
		y = (int) ((g->pos.py + dy) / BOX_SIZE);
		if (((keycode == XK_w && !g->frames[fr_up]) ||
			(keycode == XK_s && !g->frames[fr_down]) ||
			(keycode == XK_a && !g->frames[fr_left]) ||
			(keycode == XK_d && !g->frames[fr_right])) &&
				(x > 0 && y > 0 && x < g->map.l && y < g->map.h && g->map.v[y][x] == b_ground &&
				g->map.v[y][(int) ((g->pos.px - dx + WALL_COLISION) / BOX_SIZE)] == b_ground &&
				g->map.v[y][(int) ((g->pos.px - dx - WALL_COLISION) / BOX_SIZE)] == b_ground &&
				g->map.v[(int) ((g->pos.py + dy + WALL_COLISION) / BOX_SIZE)][x] == b_ground &&
				g->map.v[(int) ((g->pos.py + dy - WALL_COLISION) / BOX_SIZE)][x] == b_ground))
		{
			g->pos.px -= dx;
			g->pos.py += dy;
			g->pos.x = x;
			g->pos.y = y;
			sort_sprites(g);
			if (keycode == XK_w)
				g->frames[fr_up] = 1;
			else if (keycode == XK_s)
				g->frames[fr_down] = 1;
			else if (keycode == XK_a)
				g->frames[fr_left] = 1;
			else if (keycode == XK_d)
				g->frames[fr_right] = 1;
		}
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if ((keycode == XK_Right && !g->frames[fr_rotr]) ||
			(keycode == XK_Left && !g->frames[fr_rotl]))
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
				g->frames[fr_rotr] = 1;
			else
				g->frames[fr_rotl] = 1;
		}
	}
	return (1);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == XK_space && !g->frames[fr_door])
	{
		if (g->map.v[g->pos.y - 1][g->pos.x] == b_door)
		{
			g->opened_door_x = g->pos.x;
			g->opened_door_y = g->pos.y - 1;
			g->frames[fr_door] = 1;
			g->opened = 1;
		}
		else if (g->map.v[g->pos.y + 1][g->pos.x] == b_door)
		{
			g->opened_door_x = g->pos.x;
			g->opened_door_y = g->pos.y + 1;
			g->frames[fr_door] = 1;
			g->opened = 1;
		}
		else if (g->map.v[g->pos.y][g->pos.x - 1] == b_door)
		{
			g->opened_door_x = g->pos.x - 1;
			g->opened_door_y = g->pos.y;
			g->frames[fr_door] = 1;
			g->opened = 1;
		}
		else if (g->map.v[g->pos.y][g->pos.x + 1] == b_door)
		{
			g->opened_door_x = g->pos.x + 1;
			g->opened_door_y = g->pos.y;
			g->frames[fr_door] = 1;
			g->opened = 1;
		}
	}
	if (keycode == XK_Control_L || keycode == XK_Control_R)
	{
		if (!g->frames[fr_gun])
			g->frames[fr_gun] = 1;
		g->shoot = 1;
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
		float	alpha;
		alpha = atan(((float) x / SCALE - WIDTH / 2) / g->dpp) * 180.0 / PI; 
		g->pos.rot -= (int)  alpha / ROT_STEP;
		if (g->pos.rot < 0)
			g->pos.rot += 360 / ROT_STEP;
		else if (g->pos.rot >= 360 / ROT_STEP)
			g->pos.rot -= 360 / ROT_STEP;
	}
	return (1);
}

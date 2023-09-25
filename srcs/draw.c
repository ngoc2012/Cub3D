/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/25 11:34:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	redraw(t_game *g)
{
	int	xp;
	int	yp;
	int	*addr;

	addr = (int *)g->mlx.addr;
	yp = -1;
	while (++yp < HEIGHT)
	{
		xp = -1;
		while (++xp < WIDTH)
			*(addr++) = 0;
	}
}
 
void	render_object(t_tex *t, int *bg, int x0, int y0)
{
	int	x;
	int	y;

	x0 -= t->l / 2;
	y0 -= t->h;
	y = -1;
	while (++y < t->h)
	{
		x = -1;
		while (++x < t->l)
		{
			if (*((int*) t->addr + x + y * t->l) > 0)
				*((int*) bg + x + x0 + (y + y0) * WIDTH) = *((int*) t->addr + x + y * t->l);
		}
	}
}

void	render_backgroud(t_game *g)
{
	int	ix;
	double	ai;
	double	Apx;
	double	Apy;
	int	Ax;
	int	Ay;
	double	Bpx;
	double	Bpy;
	int	Bx;
	int	By;
	double	dpx;
	double	dpy;
	double	dA;
	double	dB;
	double	tol_h;
	double	tol_l;
	int	*addr;
	int	*addr_t;
	int	*addr_f;
	int	*addr_c;
	t_tex	*tex;

	addr_f = (int *)g->tex[FL].addr;
	addr_c = (int *)g->tex[CL].addr;
	g->pos.Ax = -1;
	g->pos.Ay = -1;
	g->pos.Bx = -1;
	g->pos.By = -1;
	// Angle tolerance 1 pixel / size
	tol_h= 1.0 / (double) g->map.h / BOX_SIZE;
	tol_l = 1.0 / (double) g->map.l / BOX_SIZE;
	ix = -1;
	while (++ix < WIDTH)
	{
		dA = 0.0;
		dB = 0.0;
		ai = g->ai[ix][g->pos.rot];
		if ((-tol_l < ai && ai < tol_l) || (180.0 - tol_l < ai) || ai < -(180.0 - tol_l))
		{
			if (ai < tol_l && ai > -tol_l)
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
			if (ai < tol_l && ai > -tol_l)
				Bx = Bpx / BOX_SIZE;
			else
				Bx = Bpx / BOX_SIZE - 1;
			By = g->pos.y;
			while (g->map.v[By][Bx] != B_WALL || g->map.v[By][Bx] != B_DOOR)
			{
				Bpx += dpx;
				Bpy += dpy;
				if (ai < tol_l && ai > -tol_l)
					Bx = Bpx / BOX_SIZE;
				else
					Bx = Bpx / BOX_SIZE - 1;
			}
			dA = INFINI;
			if (g->map.v[By][Bx] == B_DOOR && ai < tol_l && ai > -tol_l)
			{
				dB = (Bpx - g->pos.px + BOX_SIZE / 2) / cos(ai * PI / 180);
				Bpy += dpy / 2;
			}
			else if (g->map.v[By][Bx] == B_DOOR)
			{
				dB = (Bpx - g->pos.px - BOX_SIZE / 2) / cos(ai * PI / 180);
				Bpy += dpy / 2;
			}
			else
				dB = (Bpx - g->pos.px) / cos(ai * PI / 180);
			g->pos.Bx = Bx;
			g->pos.By = By;
		}
		else if ((90.0 - tol_h < ai && ai < 90.0 + tol_h) || (-90.0 - tol_h < ai && ai < -90.0 + tol_h))
		{
			if (ai > 90.0 - tol_h)
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE;
				dpy = -BOX_SIZE;
			}
			else
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
			}
			Apx = g->pos.px + (g->pos.py - Apy) * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
			dpx = BOX_SIZE * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
			if (ai < 0)
				dpx = -dpx;
			if (ai > 0.0)
				Ay = Apy / BOX_SIZE - 1;
			else
				Ay = Apy / BOX_SIZE;
			Ax = g->pos.x;
			while (g->map.v[Ay][Ax] != B_WALL || g->map.v[Ay][Ax] != B_DOOR)
			{
				Apx += dpx;
				Apy += dpy;
				if (ai > 0.0)
					Ay = Apy / BOX_SIZE - 1;
				else
					Ay = Apy / BOX_SIZE;
			}
			if (g->map.v[Ay][Ax] == B_DOOR && ai > 0.0)
			{
				dA = (g->pos.py - Apy + BOX_SIZE / 2) / sin(ai * PI / 180);
				Apx += dpx / 2;
			}
			else if (g->map.v[Ay][Ax] == B_DOOR)
			{
				dA = (g->pos.py - Apy - BOX_SIZE / 2) / sin(ai * PI / 180);
				Apx += dpx / 2;
			}
			else
				dA = (g->pos.py - Apy) / sin(ai * PI / 180);
			dB = INFINI;
			g->pos.Ax = Ax;
			g->pos.Ay = Ay;
		}
		else
		{
			// CHECKING HORIZONTAL INTERSECTIONS
			//Find A
			if (ai > 0.0)
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE;
				dpy = -BOX_SIZE;
			}
			else
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
			}
			Apx = g->pos.px + (g->pos.py - Apy) / g->tan_ai[ix][g->pos.rot];
			dpx = BOX_SIZE / g->tan_ai[ix][g->pos.rot];
			if (ai < 0)
				dpx = -dpx;
			if (Apx < 0 && Apx >= g->map.pl)
				dA = INFINI;
			else
			{
				Ax = Apx / BOX_SIZE;
				if (ai > 0.0)
					Ay = Apy / BOX_SIZE - 1;
				else
					Ay = Apy / BOX_SIZE;
				while (Apx >= 0 && Apx < g->map.pl && g->map.v[Ay][Ax] != B_WALL && g->map.v[Ay][Ax] != B_DOOR)
				{
					Apx += dpx;
					Apy += dpy;
					Ax = Apx / BOX_SIZE;
					if (ai > 0.0)
						Ay = Apy / BOX_SIZE - 1;
					else
						Ay = Apy / BOX_SIZE;
				}
				if (Apx < 0 || Apx >= g->map.pl)
					dA = INFINI;
				else
				{
					if (g->map.v[Ay][Ax] == B_DOOR && ai > 0.0)
					{
						dA = (g->pos.py - Apy + BOX_SIZE / 2) / sin(ai * PI / 180);
						Apx += dpx / 2;
					}
					else if (g->map.v[Ay][Ax] == B_DOOR)
					{
						dA = (g->pos.py - Apy - BOX_SIZE / 2) / sin(ai * PI / 180);
						Apx += dpx / 2;
					}
					else
						dA = (g->pos.py - Apy) / g->sin_ai[ix][g->pos.rot];
					g->pos.Ax = Ax;
					g->pos.Ay = Ay;
				}
			}
			//Find B
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
				dB = INFINI;
			else
			{
				if (ai > -90.0 && ai < 90.0)
					Bx = Bpx / BOX_SIZE;
				else
					Bx = Bpx / BOX_SIZE - 1;
				By = Bpy / BOX_SIZE;
				while (Bpy >= 0 && Bpy < g->map.ph && g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
				{
					Bpx += dpx;
					Bpy += dpy;
					if (ai > -90.0 && ai < 90.0)
						Bx = Bpx / BOX_SIZE;
					else
						Bx = Bpx / BOX_SIZE - 1;
					By = Bpy / BOX_SIZE;
				}
				if (Bpy < 0 || Bpy >= g->map.ph)
					dB = INFINI;
				else
				{
					if (g->map.v[By][Bx] == B_DOOR && ai > -90.0 && ai < 90.0)
					{
						dB = (Bpx - g->pos.px + BOX_SIZE / 2) / cos(ai * PI / 180);
						Bpy += dpy / 2;
					}
					else if (g->map.v[By][Bx] == B_DOOR)
					{
						dB = (Bpx - g->pos.px - BOX_SIZE / 2) / cos(ai * PI / 180);
						Bpy += dpy / 2;
					}
					else
						dB = (Bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
					g->pos.Bx = Bx;
					g->pos.By = By;
				}
			}
		}
		int	tx;
		int	ty;
		int	h_slide;
		double	h;
		double	p;
		double	d;
		if (dA > dB)
		{
			d = dB / g->cos_ai0[ix];
			tx = (int) (Bpy - BOX_SIZE * (double) By);
			if (g->map.v[By][Bx] == B_DOOR)
				tex = &g->tex[DO];
			else if (ai > -90 && ai < 90)
				tex = &g->tex[WE];
			else
				tex = &g->tex[EA];
		}
		else
		{
			d = dA / g->cos_ai0[ix];
			tx = (int) (Apx - BOX_SIZE * (double) Ax);
			if (g->map.v[Ay][Ax] == B_DOOR)
				tex = &g->tex[DO];
			else if (ai > 0)
				tex = &g->tex[NO];
			else
				tex = &g->tex[SO];
		}
		if (d < 0)
			d = -d;
		h = BOX_SIZE / d * g->dpp;
		p = 1.0 / d * g->dpp;
		h_slide = (int) (BOX_SIZE / d * g->dpp);
		if (h_slide > HEIGHT)
			h_slide = HEIGHT;
		int	yp;
		addr = (int *)g->mlx.addr;
		addr_t = (int *)tex->addr;
		addr += ix;
		int	start = HEIGHT / 2 - h_slide / 2;
		double	dh;
		int	xh;
		int	yh;
		double	xph;
		double	yph;
		yp = -1;
		while (++yp < start)
		{
			if (HEIGHT / 2 - yp)
			{
				dh = g->dpp * BOX_SIZE / 2 / (HEIGHT / 2 - yp) * g->cos_ai0[ix];
				xph = g->pos.px + dh * g->cos_ai[ix][g->pos.rot];
				yph = g->pos.py - dh * g->sin_ai[ix][g->pos.rot];
				xh = (int) (xph - ((int) (xph / BOX_SIZE)) * BOX_SIZE);
				yh = (int) (yph - ((int) (yph / BOX_SIZE)) * BOX_SIZE);
				if (xh < BOX_SIZE && xh >= 0 && yh < BOX_SIZE && yh >= 0)
					*addr = *(addr_c + xh + yh * g->tex[CL].l);
			}
			addr += WIDTH;
		}
		yp = -1;
		while (++yp < h_slide)
		{
			ty = (int) (((h - (double) h_slide) / 2.0 + (double) yp) / p);
			if (tx < BOX_SIZE && tx >= 0 && ty < BOX_SIZE && ty >= 0)
				*addr = *(addr_t + tx + ty * tex->l);
			addr += WIDTH;
		}
		yp = start + h_slide - 1;
		while (++yp < HEIGHT)
		{
			dh = g->dpp * BOX_SIZE / 2 / (yp - HEIGHT / 2) * g->cos_ai0[ix];
			xph = g->pos.px + dh * g->cos_ai[ix][g->pos.rot];
			yph = g->pos.py - dh * g->sin_ai[ix][g->pos.rot];
			xh = (int) (xph - ((int) (xph / BOX_SIZE)) * BOX_SIZE);
			yh = (int) (yph - ((int) (yph / BOX_SIZE)) * BOX_SIZE);
			if (xh < BOX_SIZE && xh >= 0 && yh < BOX_SIZE && yh >= 0)
				*addr = *(addr_f + xh + yh * g->tex[FL].l);
			addr += WIDTH;
		}
	}
}

void	scale_window(t_game *g)
{
	if (SCALE > 1)
	{
		int	x;
		int	y;
		y = HEIGHT * SCALE;
		while (--y >= 0)
		{

			x = WIDTH * SCALE;
			while (--x >= 0)
				*((int*) g->mlx.addr_scale + x + y * WIDTH * SCALE) = *((int*) g->mlx.addr + x / SCALE + y / SCALE * WIDTH);
		}
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img_scale, 0, 0);
	}
	else
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
}

void	draw_map(t_game *g)
{
	int	i = -1;
	int	j = -1;

	while (++i < g->map.h)
	{
		j = -1;
		while (++j < g->map.l)
		{
			if (i == g->pos.y && j == g->pos.x)
				printf(COLOR_BOLD_SLOW_BLINKING_RED "x" COLOR_OFF);
			else if (i == g->pos.Ay && j == g->pos.Ax && i == g->pos.By && j == g->pos.Bx)
				printf(COLOR_BOLD_SLOW_BLINKING_CYAN "%d" COLOR_OFF, g->map.v[i][j]);
			else if (i == g->pos.Ay && j == g->pos.Ax)
				printf(COLOR_BOLD_SLOW_BLINKING_BLUE "%d" COLOR_OFF, g->map.v[i][j]);
			else if (i == g->pos.By && j == g->pos.Bx)
				printf(COLOR_BOLD_SLOW_BLINKING_GREEN "%d" COLOR_OFF, g->map.v[i][j]);
			else
				printf("%d", g->map.v[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

int	draw(t_game *g)
{
	int	i;

	if (g->frames[FR_UP] > TRANS_SPEED)
		g->frames[FR_UP] = 0;
	if (g->frames[FR_DOWN] > TRANS_SPEED)
		g->frames[FR_DOWN] = 0;
	if (g->frames[FR_RIGHT] > ROT_SPEED)
		g->frames[FR_RIGHT] = 0;
	if (g->frames[FR_LEFT] > ROT_SPEED)
		g->frames[FR_LEFT] = 0;
	if (g->frames[FR_GUN] > GUN_SPEED)
		g->frames[FR_GUN] = 0;
	if (g->frames[FR_GUN] == 1)
		g->gun_tex = &g->gun[1];
	else if (g->frames[FR_GUN] == 2)
		g->gun_tex = &g->gun[2];
	else
		g->gun_tex = &g->gun[0];
	i = -1;
	while (++i < N_FRAMES)
		if (g->frames[i])
			g->frames[i]++;
	render_backgroud(g);
	render_object(g->gun_tex, (int *) g->mlx.addr, WIDTH / 2, HEIGHT);
	scale_window(g);
	draw_mini_map(g);
	return (1);
}

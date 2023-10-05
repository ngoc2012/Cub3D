/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/04 17:59:31 by ngoc             ###   ########.fr       */
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
			int	color = *((int*) t->addr + x + y * t->l);
			if (color > 0)
				*((int*) bg + x + x0 + (y + y0) * WIDTH) = color;
		}
	}
}

void	render_backgroud(t_game *g)
{
	int	ix;
	float	ai;
	float	Apx;
	float	Apy;
	int	Ax;
	int	Ay;
	float	Bpx;
	float	Bpy;
	int	Bx;
	int	By;
	float	dpx;
	float	dpy;
	float	dA;
	float	dB;
	float	tol_h;
	float	tol_l;
	int	*addr;
	int	*addr_t;
	int	*addr_f;
	int	*addr_c;
	int	door_coor;
	t_tex	*tex;

	addr_f = (int *)g->tex[FL].addr;
	addr_c = (int *)g->tex[CL].addr;
	g->pos.Ax = -1;
	g->pos.Ay = -1;
	g->pos.Bx = -1;
	g->pos.By = -1;
	// Angle tolerance 1 pixel / size
	tol_h= 1.0 / (float) g->map.h / BOX_SIZE;
	tol_l = 1.0 / (float) g->map.l / BOX_SIZE;
	t_sprite	*sp = 0;
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
			door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
			while ((g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
				|| (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == B_DOOR && door_coor < g->hidden_door))
			{
				Bpx += dpx;
				Bpy += dpy;
				if (ai < tol_l && ai > -tol_l)
					Bx = Bpx / BOX_SIZE;
				else
					Bx = Bpx / BOX_SIZE - 1;
				if (g->map.v[By][Bx] == B_DOOR)
					door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
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
			door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
			while ((g->map.v[Ay][Ax] != B_WALL && g->map.v[Ay][Ax] != B_DOOR)
				|| (Ay == g->opened_door_y && Ax == g->opened_door_x && g->map.v[Ay][Ax] == B_DOOR && door_coor < g->hidden_door))
			{
				Apx += dpx;
				Apy += dpy;
				if (ai > 0.0)
					Ay = Apy / BOX_SIZE - 1;
				else
					Ay = Apy / BOX_SIZE;
				door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
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
				door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
				while ((Ax >= 0 && Ax < g->map.l) && (Ay >= 0 && Ay < g->map.h) &&
					((g->map.v[Ay][Ax] != B_WALL && g->map.v[Ay][Ax] != B_DOOR)
					|| (Ay == g->opened_door_y && Ax == g->opened_door_x && g->map.v[Ay][Ax] == B_DOOR && door_coor < g->hidden_door)))
				{
					Apx += dpx;
					Apy += dpy;
					Ax = Apx / BOX_SIZE;
					if (ai > 0.0)
						Ay = Apy / BOX_SIZE - 1;
					else
						Ay = Apy / BOX_SIZE;
					door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
					//printf("Apx = %f, Ax = %d, Ay = %d\n", Apx, Ax, Ay);
				}
				if (Ax < 0 || Ax >= g->map.l || Ay < 0 || Ay >= g->map.h)
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
				door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
				//while ((Bpy >= 0 && Bpy < g->map.ph) &&
				while ((Bx >= 0 && Bx < g->map.l) && (By >= 0 && By < g->map.h) &&
					((g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
				|| (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == B_DOOR && door_coor < g->hidden_door)))
				{
					Bpx += dpx;
					Bpy += dpy;
					if (ai > -90.0 && ai < 90.0)
						Bx = Bpx / BOX_SIZE;
					else
						Bx = Bpx / BOX_SIZE - 1;
					By = Bpy / BOX_SIZE;
					door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
				}
				//if (Bpy < 0 || Bpy >= g->map.ph)
				if (Bx < 0 || Bx >= g->map.l || By < 0 || By >= g->map.h)
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
		float	h;
		float	p;
		float	d;
		if (dA > dB)
		{
			d = dB / g->cos_ai0[ix];
			tx = (int) (Bpy - BOX_SIZE * (float) By);
			if (g->map.v[By][Bx] == B_DOOR)
			{
				if (By == g->opened_door_y && Bx == g->opened_door_x)
					tx -= g->hidden_door;
				tex = &g->tex[DO];
			}
			else if (ai > -90 && ai < 90)
				tex = &g->tex[WE];
			else
				tex = &g->tex[EA];
		}
		else
		{
			d = dA / g->cos_ai0[ix];
			tx = (int) (Apx - BOX_SIZE * (float) Ax);
			if (g->map.v[Ay][Ax] == B_DOOR)
			{
				if (Ay == g->opened_door_y && Ax == g->opened_door_x)
					tx -= g->hidden_door;
				tex = &g->tex[DO];
			}
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
		float	dh;
		int	xh;
		int	yh;
		float	xph;
		float	yph;
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
		if (tx < BOX_SIZE && tx >= 0)
		{
			yp = -1;
			while (++yp < h_slide)
			{
				ty = (int) (((h - (float) h_slide) / 2.0 + (double) yp) / p);
				if (ty < BOX_SIZE && ty >= 0)
					*addr = *(addr_t + tx + ty * tex->l);
				addr += WIDTH;
			}
		}
		else
			addr += h_slide * WIDTH;
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

		// sprite
		float	dsp;
		int	i = -1;
		while (++i < g->n_sprites)
		{
			tex = g->sprites[i].tex;
			//tex = &g->sp_tex[0];
			addr_t = (int *)tex->addr;
			if (g->cos_a1[g->pos.rot] * (g->sprites[i].px - g->pos.px) - g->sin_a1[g->pos.rot] * (g->sprites[i].py - g->pos.py) >= 0)
			{
				g->eq.a1 =  g->cos_a1[g->pos.rot];
				g->eq.b1 = -g->sin_a1[g->pos.rot];
				g->eq.c1 = g->eq.a1 * g->sprites[i].px + g->eq.b1 * g->sprites[i].py;
				g->eq.a2 = -g->sin_ai[ix][g->pos.rot];
				g->eq.b2 = -g->cos_ai[ix][g->pos.rot];
				g->eq.c2 = g->eq.a2 * g->pos.px + g->eq.b2 * g->pos.py;
				g->eq.det = 1.0;
				g->eq.getXY(&g->eq);
				float	start_x = g->sprites[i].px - tex->l / 2 * g->sin_a1[g->pos.rot];
				float	start_y = g->sprites[i].py - tex->l / 2 * g->cos_a1[g->pos.rot];
				float	end_x = start_x + tex->l * g->sin_a1[g->pos.rot];
				float	end_y = start_y + tex->l * g->cos_a1[g->pos.rot];
				if ((start_x - g->eq.x) * (end_x - g->eq.x) + (start_y - g->eq.y) * (end_y - g->eq.y) <= 0)
				{
					if ((45.0 < ai && ai < 135.0) || (-135.0 < ai && ai < -45.0))
						dsp = (g->eq.x - g->pos.px) / g->cos_ai[ix][g->pos.rot];
					else
						dsp = (g->eq.y - g->pos.py) / g->sin_ai[ix][g->pos.rot];
					if (dsp < 0)
						dsp = -dsp;
					dsp /= g->cos_ai0[ix];
					if (dsp < d)
					{
						if ((45.0 < g->a1[g->pos.rot] && g->a1[g->pos.rot] < 135.0) ||
							(-135.0 < g->a1[g->pos.rot] && g->a1[g->pos.rot] < -45.0))
							tx = (int) ((g->eq.x - start_x + 0.5) / (end_x - start_x) * (float) tex->l) - 1;
						else
							tx = (int) ((g->eq.y - start_y + 0.5) / (end_y - start_y) * (float) tex->l) - 1;
						//	tx = (int) ((g->eq.x - start_x) / (end_x - start_x) * (float) tex->l);
						//else
						//	tx = (int) ((g->eq.y - start_y) / (end_y - start_y) * (float) tex->l);
						if (tx < 0)
							tx = 0;
						//if (tx > tex->l - 1)
						//	tx = tex->l - 1;
						h = tex->h / dsp * g->dpp;
						p = 1.0 / dsp * g->dpp;
						int	h_slide0 = (int) (BOX_SIZE / dsp * g->dpp);
						h_slide = (int) (tex->h / dsp * g->dpp);
						if (h_slide > HEIGHT)
							h_slide = HEIGHT;
						int	start = HEIGHT / 2 + h_slide0 / 2 - h_slide;
						if (start < 0)
							start = 0;
						if (start > HEIGHT - 1)
							start = HEIGHT - 1;
						addr = (int *)g->mlx.addr;
						addr += ix + start * WIDTH;
						yp = -1;
						while (++yp < h_slide)
						{
							ty = (int) (((h - (float) h_slide) / 2.0 + (double) yp + 0.5) / p - 1);
							//ty = (int) (((h - (float) h_slide) / 2.0 + (double) yp) / p);
							if (ty < 0)
								ty = 0;
							//if (ty > tex->h - 1)
							//	ty = tex->h - 1;
							int	color;
							color = *(addr_t + tx + ty * tex->l);
							if (color > 0)
								*addr = color;
							addr += WIDTH;
						}
						if (g->shoot && g->sprites[i].type == B_SPRITE && g->sprites[i].state != DIE && (ix == WIDTH / 2 || ix == WIDTH / 2 - 1))
							sp = &g->sprites[i];
					}
				}
			}
		}
	}
	if (g->shoot && sp)
	{
		sp->health--;
		if (!sp->health)
		{
			sp->state = DIE;
			sp->i_tex = 0;
		}
	}
	g->shoot = 0;
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
			//else if (i == g->pos.Ay && j == g->pos.Ax && i == g->pos.By && j == g->pos.Bx)
			//	printf(COLOR_BOLD_SLOW_BLINKING_CYAN "%d" COLOR_OFF, g->map.v[i][j]);
			//else if (i == g->pos.Ay && j == g->pos.Ax)
			//	printf(COLOR_BOLD_SLOW_BLINKING_BLUE "%d" COLOR_OFF, g->map.v[i][j]);
			//else if (i == g->pos.By && j == g->pos.Bx)
			//	printf(COLOR_BOLD_SLOW_BLINKING_GREEN "%d" COLOR_OFF, g->map.v[i][j]);
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

	if (g->frames[FR_DOOR])
	{
		if (g->pos.x != g->opened_door_x ||  g->pos.y != g->opened_door_y)
		{
			if (g->opened && g->hidden_door < BOX_SIZE)
				g->hidden_door += DOOR_SPEED;
			else if (g->hidden_door == BOX_SIZE && g->frames[FR_DOOR] < DOOR_IDLE)
			{
				g->map.v[g->opened_door_y][g->opened_door_x] = B_GROUND;
				g->frames[FR_DOOR]++;
			}
			else if (g->hidden_door == BOX_SIZE && g->frames[FR_DOOR] == DOOR_IDLE)
			{
				g->map.v[g->opened_door_y][g->opened_door_x] = B_DOOR;
				g->hidden_door -= DOOR_SPEED;
				g->opened = 0;
			}
			else if (g->hidden_door && g->hidden_door < BOX_SIZE && g->frames[FR_DOOR] == DOOR_IDLE)
				g->hidden_door -= DOOR_SPEED;
			else
				g->frames[FR_DOOR] = 0;
		}
	}
	if (g->frames[FR_UP] > TRANS_SPEED)
		g->frames[FR_UP] = 0;
	if (g->frames[FR_DOWN] > TRANS_SPEED)
		g->frames[FR_DOWN] = 0;
	if (g->frames[FR_LEFT] > TRANS_SPEED)
		g->frames[FR_LEFT] = 0;
	if (g->frames[FR_RIGHT] > TRANS_SPEED)
		g->frames[FR_RIGHT] = 0;
	if (g->frames[FR_ROT_R] > ROT_SPEED)
		g->frames[FR_ROT_R] = 0;
	if (g->frames[FR_ROT_L] > ROT_SPEED)
		g->frames[FR_ROT_L] = 0;
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
		if (i != FR_DOOR && g->frames[i])
			g->frames[i]++;
	i = -1;
	while (++i < g->n_sprites)
	{
		if (g->sprites[i].type == B_SPRITE)
		{
			if (g->sprites[i].state == NORMAL)
			{
				g->sprites[i].tex = &g->sp_tex[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
				if (g->sprites[i].i_tex == (SPRITE_STATE * 3))
					g->sprites[i].i_tex = 0;
			}
			else if (g->sprites[i].state == DIE && g->sprites[i].i_tex < (SPRITE_STATE * 5))
			{
				g->sprites[i].tex = &g->sp_hit[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
			}
		}

	}
	//draw_map(g);
	render_backgroud(g);
	render_object(g->gun_tex, (int *) g->mlx.addr, WIDTH / 2, HEIGHT);
	draw_mini_map(g);
	scale_window(g);
	return (1);
}

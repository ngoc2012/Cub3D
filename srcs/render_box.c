/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 10:07:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	*render_ceiling(t_game *g, int ix, int start)
{
	int			yp;
	int			*addr;
	int			*addr_c;
	t_render	r;

	addr = (int *)g->mlx.addr + ix;
	addr_c = (int *)g->tex[CL].addr;
	yp = -1;
	while (++yp < start)
	{
		if (g->cl_color)
			*addr = g->cl_color;
		else
		{
			r.dh = g->dpp * BOX_SIZE / 2 / (HEIGHT / 2 - yp) * g->cos_ai0[ix];
			r.xph = g->pos.px + r.dh * g->cos_ai[ix][g->pos.rot];
			r.yph = g->pos.py - r.dh * g->sin_ai[ix][g->pos.rot];
			r.xh = (int)(r.xph - ((int)(r.xph / BOX_SIZE)) * BOX_SIZE);
			r.yh = (int)(r.yph - ((int)(r.yph / BOX_SIZE)) * BOX_SIZE);
			if (r.xh < BOX_SIZE && r.xh >= 0 && r.yh < BOX_SIZE && r.yh >= 0)
				*addr = *(addr_c + r.xh + r.yh * g->tex[CL].l);
		}
		addr += WIDTH;
	}
	return (addr);
}

static void	render_floor(t_game *g, int ix, int yp, int *addr)
{
	int			*addr_f;
	t_render	r;

	addr_f = (int *)g->tex[FL].addr;
	while (++yp < HEIGHT)
	{
		if (g->fl_color)
			*addr = g->fl_color;
		else
		{
			r.dh = g->dpp * BOX_SIZE / 2 / (yp - HEIGHT / 2) * g->cos_ai0[ix];
			r.xph = g->pos.px + r.dh * g->cos_ai[ix][g->pos.rot];
			r.yph = g->pos.py - r.dh * g->sin_ai[ix][g->pos.rot];
			r.xh = (int)(r.xph - ((int)(r.xph / BOX_SIZE)) * BOX_SIZE);
			r.yh = (int)(r.yph - ((int)(r.yph / BOX_SIZE)) * BOX_SIZE);
			if (r.xh < BOX_SIZE && r.xh >= 0 && r.yh < BOX_SIZE && r.yh >= 0)
				*addr = *(addr_f + r.xh + r.yh * g->tex[FL].l);
		}
		addr += WIDTH;
	}
}

static void	render_all(t_game *g, int ix, t_render *r, int h_slide)
{
	int		*addr;
	int		yp;
	int		start;
	float	h;
	float	p;

	h = BOX_SIZE / r->d * g->dpp;
	p = 1.0 / r->d * g->dpp;
	start = HEIGHT / 2 - h_slide / 2;
	addr = render_ceiling(g, ix, start);
	if (r->tx < BOX_SIZE && r->tx >= 0)
	{
		yp = -1;
		while (++yp < h_slide)
		{
			r->ty = (int)(((h - (float) h_slide) / 2.0 + (double) yp) / p);
			if (r->ty < BOX_SIZE && r->ty >= 0)
				*addr = *((int *)r->tex->addr + r->tx + r->ty * r->tex->l);
			addr += WIDTH;
		}
	}
	else
		addr += h_slide * WIDTH;
	render_floor(g, ix, start + h_slide - 1, addr);
}

static void	get_tex(t_game *g, int ix, t_render *r)
{
	if (g->pos.dA > g->pos.dB)
	{
		r->tex = &g->tex[EA];
		if (g->map.v[g->pos.By][g->pos.Bx] == B_DOOR)
		{
			if (g->pos.By == g->opened_door_y && g->pos.Bx == g->opened_door_x)
				r->tx -= g->hidden_door;
			r->tex = &g->tex[DO];
		}
		else if (g->ai[ix][g->pos.rot] > -90 && g->ai[ix][g->pos.rot] < 90)
			r->tex = &g->tex[WE];
	}
	else
	{
		r->tex = &g->tex[SO];
		if (g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR)
		{
			if (g->pos.Ay == g->opened_door_y && g->pos.Ax == g->opened_door_x)
				r->tx -= g->hidden_door;
			r->tex = &g->tex[DO];
		}
		else if (g->ai[ix][g->pos.rot] > 0)
			r->tex = &g->tex[NO];
	}
}

float	render_box(t_game *g, int ix)
{
	t_render	r;
	int			h_slide;

	get_ab(g, ix);
	if (g->pos.dA > g->pos.dB)
	{
		r.d = g->pos.dB / g->cos_ai0[ix];
		r.tx = (int)(g->pos.Bpy - BOX_SIZE * (float) g->pos.By);
	}
	else
	{
		r.d = g->pos.dA / g->cos_ai0[ix];
		r.tx = (int)(g->pos.Apx - BOX_SIZE * (float) g->pos.Ax);
	}
	if (r.d < 0)
		r.d = -r.d;
	get_tex(g, ix, &r);
	h_slide = (int)(BOX_SIZE / r.d * g->dpp);
	if (h_slide > HEIGHT)
		h_slide = HEIGHT;
	render_all(g, ix, &r, h_slide);
	return (r.d);
}

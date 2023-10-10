/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/10/10 13:54:26 by nbechon          ###   ########.fr       */
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
	addr_c = (int *)g->tex[t_cl].addr;
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
				*addr = *(addr_c + r.xh + r.yh * g->tex[t_cl].l);
		}
		addr += WIDTH;
	}
	return (addr);
}

static void	render_floor(t_game *g, int ix, int yp, int *addr)
{
	int			*addr_f;
	t_render	r;

	addr_f = (int *)g->tex[t_fl].addr;
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
				*addr = *(addr_f + r.xh + r.yh * g->tex[t_fl].l);
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
	if (g->pos.da > g->pos.db)
	{
		r->tex = &g->tex[t_ea];
		if (g->map.v[g->pos.by][g->pos.bx] == b_door)
		{
			if (g->pos.by == g->opened_door_y && g->pos.bx == g->opened_door_x)
				r->tx -= g->hidden_door;
			r->tex = &g->tex[t_do];
		}
		else if (g->ai[ix][g->pos.rot] > -90 && g->ai[ix][g->pos.rot] < 90)
			r->tex = &g->tex[t_we];
	}
	else
	{
		r->tex = &g->tex[t_so];
		if (g->map.v[g->pos.ay][g->pos.ax] == b_door)
		{
			if (g->pos.ay == g->opened_door_y && g->pos.ax == g->opened_door_x)
				r->tx -= g->hidden_door;
			r->tex = &g->tex[t_do];
		}
		else if (g->ai[ix][g->pos.rot] > 0)
			r->tex = &g->tex[t_no];
	}
}

float	render_box(t_game *g, int ix)
{
	t_render	r;
	int			h_slide;

	get_ab(g, ix);
	if (g->pos.da > g->pos.db)
	{
		r.d = g->pos.db / g->cos_ai0[ix];
		r.tx = (int)(g->pos.bpy - BOX_SIZE * (float) g->pos.by);
	}
	else
	{
		r.d = g->pos.da / g->cos_ai0[ix];
		r.tx = (int)(g->pos.apx - BOX_SIZE * (float) g->pos.ax);
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

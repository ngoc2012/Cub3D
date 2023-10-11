/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/11 15:50:18 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	g_s(t_game *g, t_render *r, int hs)
{
	int	start;

	start = HEIGHT / 2 + (int)(BOX_SIZE / r->d * g->dpp) / 2 - hs;
	if (start < 0)
		start = 0;
	if (start > HEIGHT - 1)
		start = HEIGHT - 1;
	return (start);
}

static void	render(t_game *g, t_tex *tex, t_render *r)
{
	int	hs;
	int	*addr;
	int	yp;
	int	color;

	r->h = tex->h / r->d * g->dpp;
	r->p = 1.0 / r->d * g->dpp;
	hs = (int)(tex->h / r->d * g->dpp);
	if (hs > HEIGHT)
		hs = HEIGHT;
	addr = (int *)g->mlx.addr + r->ix + g_s(g, r, hs) * WIDTH;
	yp = -1;
	while (++yp < hs)
	{
		r->ty = (int)(((r->h - (float) hs) / 2.0 + \
		(double) yp + 0.5) / r->p - 1);
		if (r->ty < 0)
			r->ty = 0;
		color = *((int *)tex->addr + r->tx + r->ty * tex->l);
		if (color > 0 && addr - WIDTH * HEIGHT < (int *)g->mlx.addr)
			*addr = color;
		addr += WIDTH;
	}
}

static void	math(t_game *g, t_tex *tex, t_render *r)
{
	g->eq.a1 = g->cos_a1[g->pos.rot];
	g->eq.b1 = -g->sin_a1[g->pos.rot];
	g->eq.c1 = g->eq.a1 * g->sprites[r->i].px + g->eq.b1 * g->sprites[r->i].py;
	g->eq.a2 = -g->sin_ai[r->ix][g->pos.rot];
	g->eq.b2 = -g->cos_ai[r->ix][g->pos.rot];
	g->eq.c2 = g->eq.a2 * g->pos.px + g->eq.b2 * g->pos.py;
	g->eq.det = 1.0;
	g->eq.get_xy(&g->eq);
	r->start_x = g->sprites[r->i].px - tex->l / 2 * g->sin_a1[g->pos.rot];
	r->start_y = g->sprites[r->i].py - tex->l / 2 * g->cos_a1[g->pos.rot];
	r->end_x = r->start_x + tex->l * g->sin_a1[g->pos.rot];
	r->end_y = r->start_y + tex->l * g->cos_a1[g->pos.rot];
}

static void	render_all(t_game *g, t_tex *tex, t_render *r, t_sprite **sp)
{
	if (r->d < 0)
		r->d = -r->d;
	r->d /= g->cos_ai0[r->ix];
	if (r->d < r->d0)
	{
		if ((45.0 < g->a1[g->pos.rot] && g->a1[g->pos.rot] < 135.0)
			|| (-135.0 < g->a1[g->pos.rot] && g->a1[g->pos.rot] < -45.0))
			r->tx = (int)((g->eq.x - r->start_x + 0.5) / \
			(r->end_x - r->start_x) * (float) tex->l) - 1;
		else
			r->tx = (int)((g->eq.y - r->start_y + 0.5) / \
			(r->end_y - r->start_y) * (float) tex->l) - 1;
		if (r->tx < 0)
			r->tx = 0;
		render(g, tex, r);
		if (g->shoot && g->sprites[r->i].type == b_sprite
			&& g->sprites[r->i].state != s_die
			&& (r->ix == WIDTH / 2 || r->ix == WIDTH / 2 - 1))
			*sp = &g->sprites[r->i];
	}
}

void	render_sprites(t_game *g, int ix, float d0, t_sprite **sp)
{
	t_render	r;
	float		ai;

	r.i = -1;
	r.ix = ix;
	r.d0 = d0;
	ai = g->ai[r.ix][g->pos.rot];
	while (++r.i < g->n_sprites)
	{
		if (g->cos_a1[g->pos.rot] * (g->sprites[r.i].px - g->pos.px) - \
			g->sin_a1[g->pos.rot] * (g->sprites[r.i].py - g->pos.py) >= 0)
		{
			math(g, g->sprites[r.i].tex, &r);
			if ((r.start_x - g->eq.x) * (r.end_x - g->eq.x) + \
				(r.start_y - g->eq.y) * (r.end_y - g->eq.y) <= 0)
			{
				if ((45.0 < ai && ai < 135.0) || (-135.0 < ai && ai < -45.0))
					r.d = (g->eq.x - g->pos.px) / g->cos_ai[r.ix][g->pos.rot];
				else
					r.d = (g->eq.y - g->pos.py) / g->sin_ai[r.ix][g->pos.rot];
				render_all(g, g->sprites[r.i].tex, &r, sp);
			}
		}
	}
}

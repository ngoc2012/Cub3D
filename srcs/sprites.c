/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/07 12:26:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_sprites(t_game *g, int ix, float d, t_sprite **sp)
{
	// sprite
	int	tx;
	int	ty;
	int	h_slide;
	float	h;
	float	p;
	int	*addr;
	int	*addr_t;
	t_tex	*tex;
	float	dsp;
	int	i = -1;
	float	ai = g->ai[ix][g->pos.rot];
	int	yp;

	while (++i < g->n_sprites)
	{
		tex = g->sprites[i].tex;
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
					if (tx < 0)
						tx = 0;
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
						if (ty < 0)
							ty = 0;
						int	color;
						color = *(addr_t + tx + ty * tex->l);
						if (color > 0 && addr - WIDTH * HEIGHT < (int *)g->mlx.addr)
							*addr = color;
						addr += WIDTH;
					}

					if (g->shoot && g->sprites[i].type == B_SPRITE && g->sprites[i].state != DIE && (ix == WIDTH / 2 || ix == WIDTH / 2 - 1))
						*sp = &g->sprites[i];
				}
			}
		}
	}
}

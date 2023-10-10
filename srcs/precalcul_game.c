/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalcul_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/10 13:46:51 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	precalcul_init(t_game *g)
{
	int		i;
	int		j;
	float	xp;

	i = -1;
	while (++i < WIDTH)
	{
		xp = WIDTH / 2 - i + 0.5;
		g->ai0[i] = atan(xp / g->dpp) * 180.0 / PI;
		g->cos_ai0[i] = 1 / cos(g->ai0[i] * PI / 180.0);
		g->ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		g->tan_ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		g->cos_ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		g->sin_ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		j = -1;
		while (++j < 360 / ROT_STEP)
		{
			g->ai[i][j] = angle_convert(j * ROT_STEP + g->ai0[i]);
			g->tan_ai[i][j] = tan(g->ai[i][j] * PI / 180.0);
			g->cos_ai[i][j] = cos(g->ai[i][j] * PI / 180.0);
			g->sin_ai[i][j] = sin(g->ai[i][j] * PI / 180.0);
		}
	}
}

int	precalcul(t_game *g)
{
	int		j;

	g->ai0 = malloc(sizeof(float) * WIDTH);
	g->cos_ai0 = malloc(sizeof(float) * WIDTH);
	g->ai = ft_calloc(sizeof(float *), WIDTH);
	g->tan_ai = ft_calloc(sizeof(float *), WIDTH);
	g->cos_ai = ft_calloc(sizeof(float *), WIDTH);
	g->sin_ai = ft_calloc(sizeof(float *), WIDTH);
	g->a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	g->sin_a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	g->cos_a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	precalcul_init(g);
	j = -1;
	while (++j < 360 / ROT_STEP)
	{
		g->a1[j] = angle_convert(j * ROT_STEP);
		g->sin_a1[j] = sin(g->a1[j] * PI / 180.0);
		g->cos_a1[j] = cos(g->a1[j] * PI / 180.0);
	}
	g->tol_h = 1.0 / (float) g->map.h / BOX_SIZE;
	g->tol_l = 1.0 / (float) g->map.l / BOX_SIZE;
	return (1);
}

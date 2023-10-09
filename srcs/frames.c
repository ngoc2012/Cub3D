/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 07:42:19 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 08:49:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	door(t_game *g)
{
	if (g->frames[FR_DOOR]
		&& (g->pos.x != g->opened_door_x || g->pos.y != g->opened_door_y))
	{
		if (g->opened && g->hidden_door < BOX_SIZE)
			g->hidden_door += DOOR_SPEED;
		else if (g->hidden_door == BOX_SIZE
			&& g->frames[FR_DOOR] < DOOR_IDLE)
		{
			g->map.v[g->opened_door_y][g->opened_door_x] = B_GROUND;
			g->frames[FR_DOOR]++;
		}
		else if (g->hidden_door == BOX_SIZE
			&& g->frames[FR_DOOR] == DOOR_IDLE)
		{
			g->map.v[g->opened_door_y][g->opened_door_x] = B_DOOR;
			g->hidden_door -= DOOR_SPEED;
			g->opened = 0;
		}
		else if (g->hidden_door && g->hidden_door < BOX_SIZE
			&& g->frames[FR_DOOR] == DOOR_IDLE)
			g->hidden_door -= DOOR_SPEED;
		else
			g->frames[FR_DOOR] = 0;
	}
}

static void	sprite(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->n_sprites)
	{
		if (g->sprites[i].type == B_SPRITE)
		{
			if (g->sprites[i].state == NORMAL)
			{
				g->sprites[i].tex = \
				&g->sp_tex[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
				if (g->sprites[i].i_tex == (SPRITE_STATE * 3))
					g->sprites[i].i_tex = 0;
			}
			else if (g->sprites[i].state == DIE
				&& g->sprites[i].i_tex < (SPRITE_STATE * 5))
			{
				g->sprites[i].tex = \
				&g->sp_hit[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
			}
		}
	}
}

static void	gun(t_game *g)
{
	if (g->frames[FR_GUN] > GUN_SPEED)
		g->frames[FR_GUN] = 0;
	if (g->frames[FR_GUN] == 1)
		g->gun_tex = &g->gun[1];
	else if (g->frames[FR_GUN] == 2)
		g->gun_tex = &g->gun[2];
	else
		g->gun_tex = &g->gun[0];
}

void	frames(t_game *g)
{
	int	i;

	door(g);
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
	gun(g);
	i = -1;
	while (++i < N_FRAMES)
		if (i != FR_DOOR && g->frames[i])
			g->frames[i]++;
	sprite(g);
}

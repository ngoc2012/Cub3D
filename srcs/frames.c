/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/10 13:21:46 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	door(t_game *g)
{
	if (g->frames[fr_door]
		&& (g->pos.x != g->opened_door_x || g->pos.y != g->opened_door_y))
	{
		if (g->opened && g->hidden_door < BOX_SIZE)
			g->hidden_door += DOOR_SPEED;
		else if (g->hidden_door == BOX_SIZE
			&& g->frames[fr_door] < DOOR_IDLE)
		{
			g->map.v[g->opened_door_y][g->opened_door_x] = b_ground;
			g->frames[fr_door]++;
		}
		else if (g->hidden_door == BOX_SIZE
			&& g->frames[fr_door] == DOOR_IDLE)
		{
			g->map.v[g->opened_door_y][g->opened_door_x] = b_door;
			g->hidden_door -= DOOR_SPEED;
			g->opened = 0;
		}
		else if (g->hidden_door && g->hidden_door < BOX_SIZE
			&& g->frames[fr_door] == DOOR_IDLE)
			g->hidden_door -= DOOR_SPEED;
		else
			g->frames[fr_door] = 0;
	}
}

static void	sprite(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->n_sprites)
	{
		if (g->sprites[i].type == b_sprite)
		{
			if (g->sprites[i].state == s_normal)
			{
				g->sprites[i].tex = \
				&g->sp_tex[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
				if (g->sprites[i].i_tex == (SPRITE_STATE * 3))
					g->sprites[i].i_tex = 0;
			}
			else if (g->sprites[i].state == s_die
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
	if (g->frames[fr_gun] > GUN_SPEED)
		g->frames[fr_gun] = 0;
	if (g->frames[fr_gun] == 1)
		g->gun_tex = &g->gun[1];
	else if (g->frames[fr_gun] == 2)
		g->gun_tex = &g->gun[2];
	else
		g->gun_tex = &g->gun[0];
}

void	frames(t_game *g)
{
	int	i;

	door(g);
	if (g->frames[fr_up] > TRANS_SPEED)
		g->frames[fr_up] = 0;
	if (g->frames[fr_down] > TRANS_SPEED)
		g->frames[fr_down] = 0;
	if (g->frames[fr_left] > TRANS_SPEED)
		g->frames[fr_left] = 0;
	if (g->frames[fr_right] > TRANS_SPEED)
		g->frames[fr_right] = 0;
	if (g->frames[fr_rotr] > ROT_SPEED)
		g->frames[fr_rotr] = 0;
	if (g->frames[fr_rotl] > ROT_SPEED)
		g->frames[fr_rotl] = 0;
	gun(g);
	i = -1;
	while (++i < N_FRAMES)
		if (i != fr_door && g->frames[i])
			g->frames[i]++;
	sprite(g);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/11 16:04:52 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	key_release3(t_game *g)
{
	if (g->map.v[g->pos.y][g->pos.x - 1] == b_door)
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

void	key_release2(t_game *g)
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
}

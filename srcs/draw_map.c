/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/11 16:07:22 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	draw_map(t_game *g)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = -1;
// 	while (++i < g->map.h)
// 	{
// 		j = -1;
// 		while (++j < g->map.l)
// 		{
// 			if (i == g->pos.y && j == g->pos.x)
// 				printf(COLOR_BOLD_SLOW_BLINKING_RED "x" COLOR_OFF);
// 			else
// 				printf("%d", g->map.v[i][j]);
// 			printf(" ");
// 		}
// 		printf("\n");
// 	}
// }

void	free_array(float **a, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (a[i])
			free(a[i]);
	free(a);
}

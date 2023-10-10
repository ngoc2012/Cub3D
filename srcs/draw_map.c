/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/10 13:20:08 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_map(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < g->map.h)
	{
		j = -1;
		while (++j < g->map.l)
		{
			if (i == g->pos.y && j == g->pos.x)
				printf(COLOR_BOLD_SLOW_BLINKING_RED "x" COLOR_OFF);
			else
				printf("%d", g->map.v[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

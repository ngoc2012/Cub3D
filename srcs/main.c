/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/11 15:11:30 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sort_sprites2(t_game *g)
{
	t_sprite	sp;
	int			i;
	int			j;

	i = -1;
	while (++i < g->n_sprites - 1)
	{
		j = i;
		while (++j < g->n_sprites)
		{
			if (g->sprites[i].dd < g->sprites[j].dd)
			{
				sp = g->sprites[i];
				g->sprites[i] = g->sprites[j];
				g->sprites[j] = sp;
			}
		}
	}
}

void	sort_sprites(t_game *g)
{
	int			i;
	float		dx;
	float		dy;

	if (g->n_sprites < 2)
		return ;
	i = -1;
	while (++i < g->n_sprites)
	{
		dx = g->sprites[i].px - g->pos.px;
		dy = g->sprites[i].py - g->pos.py;
		g->sprites[i].dd = dx * dx + dy * dy;
	}
	sort_sprites2(g);
}

void	for_sprites(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->n_sprites)
	{
		if (g->sprites[i].type == b_d3)
			g->sprites[i].tex = &g->tex[t_d3];
		else if (g->sprites[i].type == b_d4)
			g->sprites[i].tex = &g->tex[t_d4];
		else if (g->sprites[i].type == b_d5)
			g->sprites[i].tex = &g->tex[t_d5];
		else if (g->sprites[i].type == b_d6)
			g->sprites[i].tex = &g->tex[t_d6];
	}
}

void	main_norm(t_game g)
{
	if (!g.mlx.mlx || !g.mlx.win)
		end_game(&g, EXIT_FAILURE, "Error mlx\n");
}

int	main(int argc, char **argv)
{
	t_game	g;

	(void) argc;
	init(&g);
	if (!get_map(&g, argv[1]) || !precalcul(&g))
		end_game(&g, EXIT_FAILURE, "Error map or memories\n");
	sort_sprites(&g);
	g.mlx.mlx = mlx_init();
	g.mlx.win = mlx_new_window(g.mlx.mlx, WIDTH * SCALE,
			HEIGHT * SCALE, "Cub3D");
	main_norm(g);
	g.mlx.img = mlx_new_image(g.mlx.mlx, WIDTH, HEIGHT);
	g.mlx.img_scale = mlx_new_image(g.mlx.mlx, WIDTH * SCALE, HEIGHT * SCALE);
	g.mlx.addr = mlx_get_data_addr(g.mlx.img, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	g.mlx.addr_scale = mlx_get_data_addr(g.mlx.img_scale,
			&g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	if (!get_textures(&g, argv[1]))
		end_game(&g, EXIT_FAILURE, "Error textures load\n");
	for_sprites(&g);
	mlx_mouse_hook(g.mlx.win, mouse_hook, &g);
	mlx_hook(g.mlx.win, 2, KeyPressMask, &key_press, &g);
	mlx_hook(g.mlx.win, 3, KeyReleaseMask, &key_release, &g);
	mlx_hook(g.mlx.win, ClientMessage, LeaveWindowMask, &end_game, &g);
	mlx_loop_hook(g.mlx.mlx, &draw, &g);
	mlx_loop(g.mlx.mlx);
}

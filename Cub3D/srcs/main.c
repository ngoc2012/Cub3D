/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/19 10:49:38 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	end_game(t_game *g, int exit_code, char *s)
{
	mlx_destroy_image(g->mlx.mlx, g->mlx.img);
	mlx_destroy_window(g->mlx.mlx, g->mlx.win);
	mlx_destroy_display(g->mlx.mlx);
	free(g->mlx.mlx);
	free_map(&g->map);
	if (s)
		ft_putstr_fd(s, 2);
	exit(exit_code);
}

void	init(t_game *g)
{
	g->map.h = 0;
	g->map.l = 0;
	g->pos.x = 0;
	g->pos.y = 0;
	g->pos.alpha = 90;
	g->pos.alpha = 90;
	g->dpp = (int) WIDTH / 2 / tan(PI /180 * FOV / 2);
	//printf("dpp %d\n", g->dpp);
}

int	main()
{
	t_game	g;

	init(&g);
	get_map(&g, "maps/3.cub");
	g.mlx.mlx = mlx_init();
	g.mlx.win = mlx_new_window(g.mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!g.mlx.mlx || !g.mlx.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(g.mlx.win, key_hook, &g);
	//mlx_mouse_hook(g.win, mouse_hook, p);
	//mlx_loop_hook(g.mlx, loop_hook, p);
	//mlx_hook(g.win, ClientMessage, LeaveWindowMask, &end_prog, p);
	g.mlx.img = mlx_new_image(g.mlx.mlx, WIDTH, HEIGHT);
	g.mlx.addr = mlx_get_data_addr(g.mlx.img, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	//printf("g.h = %d, g.l = %d, g.x = %d, g.y = %d, g.dx = %f, g.dy = %f\n", g.map.h , g.map.l , g.pos.x , g.pos.y , g.pos.dx , g.pos.dy);
	draw(&g);
	mlx_put_image_to_window(g.mlx.mlx, g.mlx.win, g.mlx.img, 0, 0);
	mlx_loop(g.mlx.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 21:09:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_array(float **a, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (a[i])
			free(a[i]);
	free(a);
}

int	end_game(t_game *g, int exit_code, char *s)
{
	int	i;

	i = -1;
	while (++i < N_TEX)
		if (g->tex[i].img)
			mlx_destroy_image(g->mlx.mlx, g->tex[i].img);
	i = -1;
	while (++i < 3)
		if (g->sp_tex[i].img)
			mlx_destroy_image(g->mlx.mlx, g->sp_tex[i].img);
	i = -1;
	while (++i < 3)
		if (g->sp_att[i].img)
			mlx_destroy_image(g->mlx.mlx, g->sp_att[i].img);
	i = -1;
	while (++i < 5)
		if (g->sp_hit[i].img)
			mlx_destroy_image(g->mlx.mlx, g->sp_hit[i].img);
	i = -1;
	while (++i < 3)
		if (g->gun[i].img)
			mlx_destroy_image(g->mlx.mlx, g->gun[i].img);
	if (g->mlx.img)
		mlx_destroy_image(g->mlx.mlx, g->mlx.img);
	if (g->mlx.img_scale)
		mlx_destroy_image(g->mlx.mlx, g->mlx.img_scale);
	if (g->mlx.mlx)
	{
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
	}
	if (g->map.h && g->map.l)
		free_map(&g->map);
	if (s)
		ft_putstr_fd(s, 2);
		//perror(s);
	if (g->ai0)
		free(g->ai0);
	if (g->cos_ai0)
		free(g->cos_ai0);
	if (g->ai)
		free_array(g->ai, WIDTH);
	if (g->tan_ai)
		free_array(g->tan_ai, WIDTH);
	if (g->cos_ai)
		free_array(g->cos_ai, WIDTH);
	if (g->sin_ai)
		free_array(g->sin_ai, WIDTH);
	if (g->cos_a1)
		free(g->cos_a1);
	if (g->sin_a1)
		free(g->sin_a1);
	if (g->a1)
		free(g->a1);
	if (g->n_sprites)
		free(g->sprites);
	exit(exit_code);
	return (1);
}

void	get_det(t_equa2 *e)
{
	e->det = e->a1 * e->b2 - e->b1 * e->a2;
}

void	get_xy(t_equa2 *e)
{
	e->get_det(e);
	e->x = (e->b2 * e->c1 - e->b1 * e->c2) / e->det;
	e->y = (e->c2 * e->a1 - e->c1 * e->a2) / e->det;
}

void	init(t_game *g)
{
	int	i;

	g->map.h = 0;
	g->map.l = 0;
	g->map.ph = 0;
	g->map.pl = 0;
	g->pos.x = 0;
	g->pos.y = 0;
	g->pos.rot = 0;
	g->dpp = (int) WIDTH / 2 / tan(PI /180 * FOV / 2);
	i = -1;
	while (++i < N_TEX)
		g->tex[i].img = 0;
	i = -1;
	while (++i < N_FRAMES)
		g->frames[i] = 0;
	i = -1;
	while (++i < 3)
		g->gun[i].img = 0;
	i = -1;
	while (++i < 3)
		g->sp_tex[i].img = 0;
	i = -1;
	while (++i < 3)
		g->sp_att[i].img = 0;
	i = -1;
	while (++i < 5)
		g->sp_hit[i].img = 0;
	g->mlx.mlx = 0;
	g->mlx.img = 0;
	g->mlx.img_scale = 0;
	g->ai = 0;
	g->ai0 = 0;
	g->cos_ai0 = 0;
	g->tan_ai = 0;
	g->cos_ai = 0;
	g->sin_ai = 0;
	g->cos_a1 = 0;
	g->sin_a1 = 0;
	g->a1 = 0;
	g->shoot = 0;
	g->opened_door_x = 0;
	g->opened_door_y = 0;
	g->hidden_door = 0;
	g->fl_color = 0;
	g->cl_color = 0;
	g->opened = 0;
	g->gun_tex = &g->gun[0];
	g->sprites = 0;
	g->n_sprites = 0;
	g->eq.get_det = get_det;
	g->eq.get_xy = get_xy;
}

int	precalcul(t_game *g)
{
	int		i;
	int		j;
	float	Xp;

	g->ai0 = malloc(sizeof(float) * WIDTH);
	g->cos_ai0 = malloc(sizeof(float) * WIDTH);
	g->ai = ft_calloc(sizeof(float *), WIDTH);
	g->tan_ai = ft_calloc(sizeof(float *), WIDTH);
	g->cos_ai = ft_calloc(sizeof(float *), WIDTH);
	g->sin_ai = ft_calloc(sizeof(float *), WIDTH);
	g->a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	g->sin_a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	g->cos_a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	i = -1;
	while (++i < WIDTH)
	{
		Xp = WIDTH / 2 - i + 0.5;
		g->ai0[i] = atan(Xp / g->dpp) * 180.0 / PI; 
		g->cos_ai0[i] = 1 / cos(g->ai0[i] * PI /180.0); 
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
	j = -1;
	while (++j < 360 / ROT_STEP)
	{
		g->a1[j] = angle_convert(j * ROT_STEP);
		g->sin_a1[j] = sin(g->a1[j] * PI / 180.0);
		g->cos_a1[j] = cos(g->a1[j] * PI / 180.0);
	}
	g->tol_h= 1.0 / (float) g->map.h / BOX_SIZE;
	g->tol_l = 1.0 / (float) g->map.l / BOX_SIZE;
	return (1);
}

void	sort_sprites(t_game *g)
{
	int	i;
	int	j;
	float	dx, dy;
	t_sprite	sp;

	if (g->n_sprites < 2)
		return ;
	i = -1;
	while (++i < g->n_sprites)
	{
		dx = g->sprites[i].px - g->pos.px;
		dy = g->sprites[i].py - g->pos.py;
		g->sprites[i].dd = dx * dx + dy *dy;
	}
	i = -1;
	while (++i < g->n_sprites - 1)
	{
		j = i;
		while (++j < g->n_sprites)
			if (g->sprites[i].dd < g->sprites[j].dd)
			{
				sp = g->sprites[i];
				g->sprites[i] = g->sprites[j];
				g->sprites[j] = sp;
			}
	}
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
	g.mlx.win = mlx_new_window(g.mlx.mlx, WIDTH * SCALE, HEIGHT * SCALE, "Cub3D");
	if (!g.mlx.mlx || !g.mlx.win)
		end_game(&g, EXIT_FAILURE, "Error mlx\n");
	g.mlx.img = mlx_new_image(g.mlx.mlx, WIDTH, HEIGHT);
	g.mlx.img_scale = mlx_new_image(g.mlx.mlx, WIDTH * SCALE, HEIGHT * SCALE);
	g.mlx.addr = mlx_get_data_addr(g.mlx.img, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	g.mlx.addr_scale = mlx_get_data_addr(g.mlx.img_scale, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	if (!get_textures(&g, argv[1]))
		end_game(&g, EXIT_FAILURE, "Error textures load\n");
	int	i = -1;
	while (++i < g.n_sprites)
	{
		if (g.sprites[i].type == b_d3)
			g.sprites[i].tex = &g.tex[t_d3];
		else if (g.sprites[i].type == b_d4)
			g.sprites[i].tex = &g.tex[t_d4];
		else if (g.sprites[i].type == b_d5)
			g.sprites[i].tex = &g.tex[t_d5];
		else if (g.sprites[i].type == b_d6)
			g.sprites[i].tex = &g.tex[t_d6];
	}
	//mlx_key_hook(g.mlx.win, key_hook, &g);
	mlx_mouse_hook(g.mlx.win, mouse_hook, &g);
	mlx_hook(g.mlx.win, 2, KeyPressMask, &key_press, &g);
	mlx_hook(g.mlx.win, 3, KeyReleaseMask, &key_release, &g);
	mlx_hook(g.mlx.win, ClientMessage, LeaveWindowMask, &end_game, &g);
	mlx_loop_hook(g.mlx.mlx, &draw, &g);
	//draw(&g);
	mlx_loop(g.mlx.mlx);
}

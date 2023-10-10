/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 15:33:01 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_texture(t_game *g, t_tex *t, char *path)
{
	if (t->img)
		mlx_destroy_image(g->mlx.mlx, t->img);
	t->img = mlx_xpm_file_to_image(g->mlx.mlx, path, &t->l, &t->h);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->ed);
	return (1);
}

int	suite_get_texture2(t_game *g, char **ss, char *s)
{
	if (!ft_strncmp("NO", ss[0], 3) && !get_texture(g, &g->tex[t_no], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("SO", ss[0], 3) && !get_texture(g, &g->tex[t_so], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("WE", ss[0], 3) && !get_texture(g, &g->tex[t_we], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("EA", ss[0], 3) && !get_texture(g, &g->tex[t_ea], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("DO", ss[0], 3) && !get_texture(g, &g->tex[t_do], ss[1]))
		return (return_error(s, ss));
}

int	get_texture2(t_game *g, char **ss, char *s)
{
	suite_get_texture2(g, ss, s);
	if (!ft_strncmp("FL", ss[0], 3) && !get_texture(g, &g->tex[t_fl], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("CL", ss[0], 3) && !get_texture(g, &g->tex[t_cl], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("D3", ss[0], 3) && !get_texture(g, &g->tex[t_d3], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("D4", ss[0], 3) && !get_texture(g, &g->tex[t_d4], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("t_d5", ss[0], 3) && !get_texture(g, &g->tex[t_d5], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("t_d6", ss[0], 3) && !get_texture(g, &g->tex[t_d6], ss[1]))
		return (return_error(s, ss));
	if (!ft_strncmp("F", ss[0], 2))
	{
		g->fl_color = get_color(ss[1]);
		if (!g->fl_color)
			return (return_error(s, ss));
	}
	if (!ft_strncmp("C", ss[0], 2))
	{
		g->cl_color = get_color(ss[1]);
		if (!g->cl_color)
			return (return_error(s, ss));
	}
}

void	order(t_game *g)
{
	get_texture(g, &g->sp_tex[0], "./sprites/cobra0.xpm");
	get_texture(g, &g->sp_tex[1], "./sprites/cobra1.xpm");
	get_texture(g, &g->sp_tex[2], "./sprites/cobra2.xpm");
	get_texture(g, &g->sp_att[0], "./sprites/cobraatt0.xpm");
	get_texture(g, &g->sp_att[1], "./sprites/cobraatt1.xpm");
	get_texture(g, &g->sp_att[2], "./sprites/cobraatt2.xpm");
	get_texture(g, &g->sp_hit[0], "./sprites/cobrahit0.xpm");
	get_texture(g, &g->sp_hit[1], "./sprites/cobrahit1.xpm");
	get_texture(g, &g->sp_hit[2], "./sprites/cobrahit2.xpm");
	get_texture(g, &g->sp_hit[3], "./sprites/cobrahit3.xpm");
	get_texture(g, &g->sp_hit[4], "./sprites/cobrahit4.xpm");
	get_texture(g, &g->gun[0], "./guns/gun1a.xpm");
	get_texture(g, &g->gun[1], "./guns/gun1b.xpm");
	get_texture(g, &g->gun[2], "./guns/gun1c.xpm");
	get_texture(g, &g->tex[t_no], "./walls/beamskin3.xpm");
	get_texture(g, &g->tex[t_so], "./walls/tile32.xpm");
	get_texture(g, &g->tex[t_we], "./walls/tile105.xpm");
	get_texture(g, &g->tex[t_ea], "./walls/steelwall6.xpm");
	get_texture(g, &g->tex[t_do], "./walls/bigdoor.xpm");
	get_texture(g, &g->tex[t_fl], "./walls/floorsteel.xpm");
	get_texture(g, &g->tex[t_cl], "./walls/floorskin.xpm");
	get_texture(g, &g->tex[t_d3], "./sprites/crate.xpm");
	get_texture(g, &g->tex[t_d4], "./sprites/d_table.xpm");
	get_texture(g, &g->tex[t_d5], "./sprites/d_tree.xpm");
	get_texture(g, &g->tex[t_d6], "./sprites/i_health.xpm");
}

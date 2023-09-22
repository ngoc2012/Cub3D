/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 11:46:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIDTH 1800
# define HEIGHT 1200
# define FOV 90
# define BOX_SIZE 64
# define TRANS_SPEED 20
# define ROT_SPEED 12
# define PI 3.141592654
# define INFINI INT_MAX
# define COLOR_BOLD_SLOW_BLINKING      "\033[1;5m"
# define COLOR_BOLD_SLOW_BLINKING_RED  "\033[1;5;31m"
# define COLOR_BOLD_SLOW_BLINKING_BLUE  "\033[1;5;34m"
# define COLOR_BOLD_SLOW_BLINKING_GREEN  "\033[1;5;32m"
# define COLOR_BOLD_SLOW_BLINKING_CYAN  "\033[1;5;36m"
# define COLOR_BOLD_GREEN              "\033[1;32m"
# define COLOR_BOLD_CYAN               "\033[1;36m"
# define COLOR_BOLD_BLUE               "\033[1;34m"
# define COLOR_BOLD  "\033[1m"
# define COLOR_OFF   "\033[m"

/*
Map:
- v: value 0,1
- h: height of map
- l: length of map
*/
typedef struct s_map {
	int	**v;
	int	h;
	int	l;
	int	ph;
	int	pl;
}	t_map;

/*
Player position
- x: position x
- y: position y
- px: pixel position x
- py: pixel position y
- alpha: angle de rotation
*/
typedef struct s_pos {
	int		x;
	int		y;
	double		px;
	double		py;
	int		alpha;
	int		Ax;
	int		Ay;
	int		Bx;
	int		By;
}	t_pos;

/*
mlx:
- bpp: bits par pixel
- ll: line size
- ed: endian
*/
typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	int		bpp;
	int		ll;
	int		ed;
	char	*addr;
}	t_mlx;

/*
texture, images ...:
- bpp: bits par pixel
- ll: line size
- ed: endian
*/
typedef struct s_tex {
	int		h;
	int		l;
	int		bpp;
	int		ll;
	int		ed;
	void	*img;
	char	*addr;
}	t_tex;

/*
main:
- dpp : distance to Projection Plan
*/
typedef struct s_game {
	t_map		map;
	t_pos		pos;
	t_mlx		mlx;
	int		dpp;
	t_tex	tex_n;
	t_tex	tex_s;
	t_tex	tex_w;
	t_tex	tex_e;
	int		texWidth;
	int		texHeight;
}	t_game;

void	free_map(t_map *m);
void	get_map(t_game *g, char *fn);
void	draw(t_game *g);
int	key_hook(int keycode, t_game *g);
void	end_game(t_game *g, int exit_code, char *s);
void	draw_mini_map(t_game *g);
double	angle_convert(double a);
void	redraw(t_game *g);
int	get_textures(t_game *g);

#endif

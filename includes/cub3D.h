/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:01:13 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 21:14:14 by ngoc             ###   ########.fr       */
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

# define WIDTH 600
# define HEIGHT 300
# define SCALE 4
# define FOV 90
# define BOX_SIZE 64
# define WALL_COLISION 8
# define TRANS_STEP 16
# define ROT_STEP 5
# define TRANS_SPEED 5
# define ROT_SPEED 0
# define GUN_SPEED 2
# define DOOR_SPEED 1
# define DOOR_IDLE 80
# define SPRITE_IDLE 5
# define SPRITE_STATE 6
# define HEALTH_SPRITE 2
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
# define N_TEX 11
# define N_FRAMES 8
# define MAP_CHAR " \n0123456NSWEX"

/*
t_no: North walls
t_so: South walls
t_we: West walls
t_ea: East walls
t_do: Door
t_fl: Floor
t_cl: Ceiling
t_d3: Decor 3 (3)
t_d4: Decor 4 (4)
t_d5: Decor 5 (5)
t_d6: Decor 6 (6)
*/
enum e_map {b_wall, b_ground, b_empty, b_door, \
b_sprite, b_d3, b_d4, b_d5, b_d6};
enum e_tex {t_no, t_so, t_we, t_ea, t_do, t_fl, t_cl, t_d3, t_d4, t_d5, t_d6};
enum e_frame {fr_up, fr_down, fr_left, fr_right, \
fr_rotl, fr_rotr, fr_gun, fr_door};

/*
Map:
- v: value 0,1
- h: height of map
- l: length of map
*/
typedef struct s_map {
	enum e_map	**v;
	int			h;
	int			l;
	int			ph;
	int			pl;
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
	float	px;
	float	py;
	int		rot;
	int		ax;
	int		ay;
	int		bx;
	int		by;
	float	dpx;
	float	dpy;
	float	apx;
	float	apy;
	float	bpx;
	float	bpy;
	float	da;
	float	db;
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
	void	*img_scale;
	int		bpp;
	int		ll;
	int		ed;
	char	*addr;
	char	*addr_scale;
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

enum e_sprite {s_normal, s_fire, s_freeze, s_die};
/*
Sprites
- dd: distance to character
*/
typedef struct s_sprite {
	float			px;
	float			py;
	float			dd;
	enum e_map		type;
	unsigned char	health;
	unsigned char	i_tex;
	enum e_sprite	state;
	t_tex			*tex;
}	t_sprite;

/*
Equations:
a1 * x + b1 * y = c1
a2 * x + b2 * y = c2
*/
typedef struct s_equa2	t_equa2;

struct s_equa2 {
	float	det;
	float	a1;
	float	b1;
	float	c1;
	float	a2;
	float	b2;
	float	c2;
	float	x;
	float	y;
	void	(*get_det)(t_equa2 *);
	void	(*get_xy)(t_equa2 *);
};

/*
main:
- dpp : distance to Projection Plan
*/
typedef struct s_game {
	t_map			map;
	t_pos			pos;
	t_mlx			mlx;
	int				dpp;
	int				frames[N_FRAMES];
	t_tex			tex[N_TEX];
	t_tex			gun[3];
	t_tex			sp_tex[3];
	t_tex			sp_att[3];
	t_tex			sp_hit[5];
	t_tex			*gun_tex;
	t_sprite		*sprites;
	unsigned int	n_sprites;
	unsigned int	shoot;
	int				opened_door_x;
	int				opened_door_y;
	int				hidden_door;
	int				fl_color;
	int				cl_color;
	char			opened;
	float			*ai0;
	float			*cos_ai0;
	float			**ai;
	float			**tan_ai;
	float			**cos_ai;
	float			**sin_ai;
	float			*cos_a1;
	float			*sin_a1;
	float			*a1;
	t_equa2			eq;
	float			tol_h;
	float			tol_l;
}	t_game;

typedef struct s_render {
	int		xh;
	int		yh;
	int		tx;
	int		ty;
	float	xph;
	float	yph;
	float	dh;
	float	d;
	t_tex	*tex;
}	t_render;

void	free_map(t_map *m);
int		get_map(t_game *g, char *fn);
int		draw(t_game *g);
int		key_hook(int keycode, t_game *g);
int		end_game(t_game *g, int exit_code, char *s);
void	draw_mini_map(t_game *g);
float	angle_convert(double a);
void	redraw(t_game *g);
int		get_textures(t_game *g, char *fn);
void	render_object(t_tex *t, int *bg, int x0, int y0);
void	render_backgroud(t_game *g);
void	scale_window(t_game *g);
int		key_press(int keycode, t_game *g);
int		key_release(int keycode, t_game *g);
int		mouse_hook(int button, int x, int y, t_game *g);
void	sort_sprites(t_game *g);
int		create_trgb(unsigned char t, unsigned char r,
			unsigned char g, unsigned char b);
void	render_sprites(t_game *g, int ix, float d, t_sprite **sp);
float	render_box(t_game *g, int ix);
void	get_b(t_game *g, int ix, float ai);
void	get_ab(t_game *g, int ix);
void	frames(t_game *g);

#endif

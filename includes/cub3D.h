/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/26 10:50:16 by minh-ngu         ###   ########.fr       */
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
# define SCALE 2
# define FOV 90
# define BOX_SIZE 64
# define WALL_COLISION 8
# define TRANS_STEP 32
# define ROT_STEP 5
# define TRANS_SPEED 1
# define ROT_SPEED 0
# define GUN_SPEED 2
# define DOOR_SPEED 2
# define DOOR_IDLE 2
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
# define N_FRAMES 5
# define MAP_CHAR " \n0123456NSWEX"

/*
NO: North walls
SO: South walls
WE: West walls
EA: East walls
DO: Door
FL: Floor
CL: Ceiling
D3: Decor 3 (3)
D4: Decor 4 (4)
D5: Decor 5 (5)
D6: Decor 6 (6)
*/
enum e_map {B_WALL, B_GROUND, B_EMPTY, B_DOOR, B_SPRITE, B_D3, B_D4, B_D5, B_D6};
enum e_tex {NO, SO, WE, EA, DO, FL, CL, D3, D4, D5, D6};
enum e_frame {FR_UP, FR_DOWN, FR_LEFT, FR_RIGHT, FR_GUN};

/*
Map:
- v: value 0,1
- h: height of map
- l: length of map
*/
typedef struct s_map {
	enum e_map	**v;
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
	int		rot;
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

/*
main:
- dpp : distance to Projection Plan
*/
typedef struct s_game {
	t_map		map;
	t_pos		pos;
	t_mlx		mlx;
	int		dpp;
	int		frames[N_FRAMES];
	t_tex	tex[N_TEX];
	t_tex	gun[3];
	t_tex	*gun_tex;
	int	opened_door_x;
	int	opened_door_y;
	int	hidden_door;
	double	*ai0;
	double	*cos_ai0;
	double	**ai;
	double	**tan_ai;
	double	**cos_ai;
	double	**sin_ai;
}	t_game;

void	free_map(t_map *m);
int	get_map(t_game *g, char *fn);
int	draw(t_game *g);
int	key_hook(int keycode, t_game *g);
int	end_game(t_game *g, int exit_code, char *s);
void	draw_mini_map(t_game *g);
double	angle_convert(double a);
void	redraw(t_game *g);
int	get_textures(t_game *g, char *fn);
void	render_object(t_tex *t, int *bg, int x0, int y0);
void	render_backgroud(t_game *g);
void	scale_window(t_game *g);
int	key_press(int keycode, t_game *g);
int	key_release(int keycode, t_game *g);
int	mouse_hook(int button, int x, int y, t_game *g);

#endif

#ifndef STRUCTS_H
# define STRUCTS_H

#include "cub3d.h"

typedef struct s_vi2D
{
	int	x;
	int	y;
}t_vi2D;

typedef struct s_vd2D
{
	double	x;
	double	y;
	f_vd2D	*function;
}t_vd2D;

typedef struct	s_mlx 
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr_img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_width;
	int		win_height;
}t_mlx;

typedef	struct	s_player
{
	double	ang;
	t_vd2D	pos;
	t_vd2D	dir;
	t_vd2D	plane;
	t_vi2D	map_pos;
	char tmp_map[10][10];
}t_player;

typedef struct s_raycaster
{
	t_player *pc;
	t_mlx	*render;
	t_vd2D	cam_pixel;
	t_vd2D	dir;
	t_vd2D	delta;
	t_vd2D	dist2side;
	t_vd2D	step;
	t_vd2D	dda_line;
	t_vd2D	map_hit;
	t_vd2D	wall_line;
	short int	hit_side;
	double	perp_dist;
	double	multiplier;
	double	wall_height_pixel;
}t_raycaster;

typedef	struct	s_general
{
	t_mlx	*render;
	t_player	*pc;
	t_raycaster	*ray;
}t_general;

# endif
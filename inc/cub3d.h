/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:43:32 by ivbatist          #+#    #+#             */
/*   Updated: 2023/12/01 22:45:53 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define PI 3.14159265358979323846264338327950288
# define CREATE 1
# define UPDATE 2
# define FRONT 1
# define BACK -1
# define LEFT -1
# define RIGHT 1
# define R_ANG 0.1
# define VEL	0.2
# define SIZE  64

enum
{
	V_WE = 1,
	V_EA,
	H_NO,
	H_SO
};

enum
{
	NORTH = 1,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING
};

typedef struct s_vd2D
{
	double	x;
	double	y;
}t_vd2D;

typedef struct s_vi2D
{
	int	x;
	int	y;
}t_vi2D;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}t_tex;

typedef struct s_math
{
	t_vd2D		pos;
	t_vd2D		dir;
	t_vd2D		plane;
	t_vi2D		map_pos;
	t_vd2D		ray_dir;
	t_vi2D		step_dda;
	t_vd2D		d2s;
	t_vd2D		delta;
	t_vi2D		px_tex;
	double		perp;
	double		step_render;
	double		pos_render;
	double		wall_h;
	int			wall_b;
	int			wall_e;
	int			hit_side;
	int			coordinate_wall;
}				t_math;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	int			pixel;
	int			win_h;
	int			win_w;
	char		*n;
	char		*s;
	char		*e;
	char		*w;
	t_tex		no_tex;
	t_tex		so_tex;
	t_tex		ea_tex;
	t_tex		we_tex;
	t_tex		canvas;
	char		start;
	char		*temp;
	char		*line;
	char		**copy_map;
	char		**color;
	int			ceiling;
	int			floor;
	int			check_map;
	t_math		player;
}				t_cub;

///PARSER
void		parse(t_cub *g, char *file);
void		set_player_position(t_cub *g, int i, int j);
void		check_elements(t_cub *g, char *line, int i);
void		check_color(t_cub *g, char *color, int face);
void		check_texture(t_cub *g, char *file, int face);
void		verify_name(t_cub *g, char *file, char *type);
void		check_texture_file(t_cub *g, char *file, int fd);
void		map_parse(t_cub *g, int fd);
void		valid_map(t_cub *g, int dir, int l, int c);
void		check_line(t_cub *g, char *line, int i, int c);

char		*texture_file(char *line, int begin);
char		*get_color(char *line, int begin);

int			check_walls(t_cub *g, int direction, int i, int j);
int			is_valid_color_format(char *color);
int			check_character(int c, char *check);
int			check_ifnsew(t_cub *g, char *line, int i);
int			check_ifcolors(t_cub *g, char *line, int i);
int			check_space(int c);
void		check_if_all_elements(t_cub *g);

///VECTORS
void		rot_vd2d(t_vd2D *v, double angle);
void		set_vd2d(t_vd2D *this, double x, double y);

t_vd2D		mult_vd2d(t_vd2D *v, double n);
t_vd2D		sum_vd2d(t_vd2D *v1, t_vd2D *v2);

//INIT
int			run_game(t_cub *g);
int			init_render(t_cub *g);

void		set_look(t_cub *g);
void		set_first_pos(t_cub *g, int i, int j);
void		init_cub(char *file);
void		set_map_pos(t_math *player);
void		init_player(t_math *player);
void		init_textures(t_cub *g, int size);
void		load_tex_xpm(t_cub *g, t_tex *img, char *name_xpm, int size);
void		load_tex_addr(t_cub *g, t_tex *img);

//DDA
void		set_ray(t_cub *g);
void		dda(t_cub *g);
void		run_dda(t_cub *g);
void		set_delta(t_cub *g);
void		set_dist2side(t_cub *g);

//RAYCASTER
int			rayscaster(t_cub *g);
void		set_perp(t_cub *g);
void		set_height(t_cub *g);
void		set_wall_coordinate(t_math *player);
void		raycasting(t_cub *g);

///MLX
int			my_mlx_pixel_get(t_tex *img, int point_x, int point_y);
void		canvas(t_cub *g, int flag);
void		my_mlx_pixel_put(t_cub *g, int x, int y, int color);

///RENDER
void		get_hit_point_tex_x(t_math *player);
void		set_point_tex_y(t_cub *g);
void		render_wall(t_cub *g);
int			render_horizont(t_cub *g, int bx, int by);
int			coordinate_tex(t_cub *g);

///HOOKS
int			hooks(int keypress, t_cub *g);
void		sides(t_cub *g, t_vd2D *dir, int orient);
void		front_back(t_cub *g, t_vd2D *dir, int orient);
/* void		look_right(t_cub *game);
void		look_left(t_cub *game); */
void		rot_player(t_cub *g, double angle);

///EXIT
int			error(t_cub *g, char *msg);
int			free_mlx(t_cub *g);
void		free_split(char **split);
void		free_structure(t_cub *g);
void		error_xpm(t_cub *g, char *msg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <ivbatist@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:58:50 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/17 18:59:39 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define	COPY 0
#define	SUM 1
#define	MULT 2
#define _USE_MATH_DEFINES 

//# include "structs.h"
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>	//remover, usado para strcpy na funcao de copiar o mapa
# include <math.h> 
# include <stdbool.h> 

typedef enum s_change
{
	NONE,
	ItoD,
	DtoI
}t_change;

typedef struct s_vi2D
{
	int	x;
	int	y;
}t_vi2D;

typedef struct s_vd2D
{
	double	x;
	double	y;
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
	t_vi2D	step;
	t_vd2D	dda_line;
	t_vi2D	map_hit;
	t_vd2D	wall_line;
	short int	hit_side;
	double	perp_dist;
	double	multiplier;
	double	wall_height_pixel;
	int pixel;
}t_raycaster;

typedef	struct	s_general
{
	t_mlx	*render;
	t_player	*pc;
	t_raycaster	*ray;
}t_general;



//Tratamentos de Hooks e entrada do teclado
int	handler_win(int key, t_general *game);
int handler_press(int key, t_general *game);
void    check_hooks(t_general	*game);
void	check_key_movs(int ley, t_general *game);

//Estruturais para rodar o jogo
void init_game(t_general	*game);
void init_pc(t_player *pc);
void	run_game(t_general	*game);
void    finish_game(t_general *game);

//Auxiliares de renderizacao de imagem
void	create_buffer_img(t_general *game);
 void print_ray(t_general *game, t_vd2D bg, t_vd2D end, int color);
void print_pc(t_general *game);      	//FUNCAO INACABADA, ALTERAR FOR DENTRO DELA
void	img_pix_put(t_mlx *data, int x, int y, int color);
void draw_line_with_stroke(t_general *game, t_vd2D bg, t_vd2D end, int color);
void 	print_map(t_general *game);					//FUNCAO INACABADA, ALTERAR FOR DENTRO DELA E TAMANHO PRE-ESTABELECIDO DO MAPA


t_vd2D  update_pos2dir(t_general *game, bool mov);


//Auxiliares de alteracao de mapa
void	get_pc(t_general *game); 					//FUNCAO TEMPORARIA, ALTERAR PARA AUTOMATICO
void	move_fov_left(t_general *game);
void	move_fov_right(t_general *game);
void	move_w(t_general *game);
void	move_s(t_general *game);
void	move_a(t_general *game);
void	move_d(t_general *game);
void    fill_map(t_player *pc);					//FUNCAO TEMPORARIA, ALTERAR PARA AUTOMATICO

//Utils
void    finish_game(t_general *game);
double degree_to_radians(int degree);

//Raycaster
void  raycaster(t_general *game);
void clear_ray(t_raycaster *ray);

//Metodos Vectors
void    copy_vd2D(t_vd2D *this, t_vd2D *src);
void    copy_vi2D(t_vi2D *this, t_vi2D *src);
void copy_int_to_double(t_vd2D *dest, t_vi2D *src);
void copy_double_to_int(t_vi2D *dest, t_vd2D *src);
void  init_vd2D(t_vd2D *this);
void  init_vi2D(t_vi2D *this);
void  set_vd2D(t_vd2D *this, double x, double y);
void   set_vi2D(t_vi2D *this, double x, double y);
void mult_vd2D(t_vd2D *mod, t_vd2D *this, double scalar);
void sum_vd2D(t_vd2D *mod, t_vd2D *this, t_vd2D *sum);


void print_array(char (*str)[10]);
# endif


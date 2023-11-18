/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:33:22 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/25 19:33:24 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    finish_game(t_general *game)
{
    mlx_destroy_window(game->render->mlx, game->render->win);
}

double degree_to_radians(int degree)
{
    return degree * M_PI / 180;
}

void    copy_vd2D(t_vd2D *this, t_vd2D *src)
{
    this->x = src->x;
    this->y = src->y;
}

void    copy_vi2D(t_vi2D *this, t_vi2D *src)
{
    this->x = src->x;
    this->y = src->y;
}

//OK
void   set_vd2D(t_vd2D *this, double x, double y)
{
    this->x = x;
    this->y = y;
}

void   set_vi2D(t_vi2D *this, double x, double y)
{
    this->x = x;
    this->y = y;
}

//OK
void  init_vd2D(t_vd2D *this)
{
    this->x = (double)0;
    this->y = (double)0;
}

void  init_vi2D(t_vi2D *this)
{
    this->x = (int)0;
    this->y = (int)0;
}

//OK
t_vd2D mult_vd2D(t_vd2D *that, double scalar)
{
    t_vd2D mod;

    mod.x = that->x * scalar;
    mod.y = that->y * scalar;

    return(mod);
}

//OK
t_vd2D sum_vd2D(t_vd2D *that, t_vd2D *sum)
{
    t_vd2D mod;

    mod.x = that->x + sum->x;
    mod.y = that->y + sum->y;

    return(mod);
}

t_vd2D sub_vd2D(t_vd2D *that, t_vd2D *sum)
{
    t_vd2D mod;

    mod.x = that->x - sum->x;
    mod.y = that->y - sum->y;

    return(mod);
}

t_vd2D rot_vd2D(t_vd2D *that, double rad)
{    
    t_vd2D mod;
    mod.x = that->x * cos(rad) - that->y * sin(rad);
    mod.y = that->x * sin(rad) + that->y * cos(rad);
    return mod;
}

void copy_int_to_double(t_vd2D *dest, t_vi2D *src)
{
    dest->x = (double)src->x;
    dest->y = (double)src->y;
}

void copy_double_to_int(t_vi2D *dest, t_vd2D *src)
{
    dest->x = (int)src->x;
    dest->y = (int)src->y;
}


void clear_ray(t_raycaster *ray)
{
    set_vd2D(&ray->cam_pixel, 0 , 0);
    set_vd2D(&ray->dir, 0 , 0);
    set_vd2D(&ray->delta, 0 , 0);
    set_vd2D(&ray->dist2side, 0 , 0);
    set_vi2D(&ray->step, 0 , 0);
    set_vd2D(&ray->dda_line, 0 , 0);
    set_vi2D(&ray->map_hit, 0 , 0);
    set_vd2D(&ray->wall_line, 0 , 0);
}

void    putstr(char *str)
{
    int i = 0;
    while(str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void print_array(char (*str)[10]) 
{
    for (int i = 0; i < 10; ++i) {
        putstr(str[i]);
    }
}

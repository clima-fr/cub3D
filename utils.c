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

t_vd2D    copy_vd2D(t_vd2D *this, t_vd2D *src)
{
    this->x = src->x;
    this->y = src->y;
    return (*this);
}

void   init_vd2D(t_vd2D *this, double x, double y)
{
    this->x = x;
    this->y = y;
/*     this->function[0] = copy_vd2D;
    this->function[1] = sum_vd2D;
    this->function[2] = mult_vd2D;
    this->self = */
}

t_vd2D mult_vd2D(t_vd2D *that, double scalar)
{
    t_vd2D result;

    result.x = that->x * scalar;
    result.y = that->y * scalar;

    return result;
}

t_vd2D sum_vd2D(t_vd2D *that, t_vd2D *sum)
{
    t_vd2D result;

    result.x = that->x + sum->x;
    result.y = that->y + sum->y;

    return result;
}

void clear_ray(t_raycaster *ray)
{
    init_vd2D(&ray->cam_pixel, 0 , 0);
    init_vd2D(&ray->dir, 0 , 0);
    init_vd2D(&ray->delta, 0 , 0);
    init_vd2D(&ray->dist2side, 0 , 0);
    init_vd2D(&ray->step, 0 , 0);
    init_vd2D(&ray->dda_line, 0 , 0);
    init_vd2D(&ray->map_hit, 0 , 0);
    init_vd2D(&ray->wall_line, 0 , 0);
}

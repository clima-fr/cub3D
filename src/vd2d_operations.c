/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vd2d_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:04:44 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 20:04:57 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_vd2D	sum_vd2d(t_vd2D *v1, t_vd2D *v2)
{
	t_vd2D	new;

	new.x = v1->x + v2->x;
	new.y = v1->y + v2->y;
	return (new);
}

t_vd2D	mult_vd2d(t_vd2D *v, double n)
{
	t_vd2D	new;

	new.x = v->x * n;
	new.y = v->y * n;
	return (new);
}

void	rot_vd2d(t_vd2D *v, double angle)
{
	double	x;
	double	y;

	x = v->x;
	y = v->y;
	v->x = x * cos(angle) - y * sin(angle);
	v->y = x * sin(angle) + y * cos(angle);
}

void	set_vd2d(t_vd2D *this, double x, double y)
{
	this->x = x;
	this->y = y;
}

void	set_map_pos(t_math *player)
{
	player->map_pos.x = floor(player->pos.x);
	player->map_pos.y = floor(player->pos.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:06:38 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/25 20:06:39 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vd2D  update_pos2dir(t_general *game, bool mov)
{
    t_vd2D new_pos;
    double  speed;

    speed = 1;
    if(mov)
        speed = 0.1;
    new_pos.x = game->pc->pos.x +  game->pc->dir.x * speed;
    new_pos.y = game->pc->pos.y +  game->pc->dir.y * speed;
    return(new_pos);
}

void reset_rad(double *pc_ang)
{
   if(*pc_ang < 0)
      *pc_ang += 2 * M_PI;
   else if(*pc_ang >= 2 * M_PI)
      *pc_ang -= 2 * M_PI;
}

void	move_fov_left(t_general *game)
{
    game->pc->ang -= 0.1;
    reset_rad(&game->pc->ang);
    game->pc->dir.x = cos(game->pc->ang) * 50;
    game->pc->dir.y = sin(game->pc->ang) * 50;
    update_img(game);
}

void	move_fov_right(t_general *game)
{
    game->pc->ang += 0.1;
   reset_rad(&game->pc->ang);
    game->pc->dir.x = cos(game->pc->ang) * 50;
    game->pc->dir.y = sin(game->pc->ang) * 50;
    update_img(game);
}

void	move_w(t_general *game)
{
    game->pc->pos = update_pos2dir(game, true);
    update_img(game);
}

void	move_s(t_general *game)
{
    game->pc->pos.x -=  game->pc->dir.x * 100;
    game->pc->pos.y -=  game->pc->dir.y * 100;
    update_img(game);
}

void	move_a(t_general *game)
{
    double rightX = -(game->pc->dir.y);
    double rightY = game->pc->dir.x;
    game->pc->pos.x -= rightX * 100;
    game->pc->pos.y -= rightY * 100;
    update_img(game);
}

void	move_d(t_general *game)
{
    double rightX = -(game->pc->dir.y);
    double rightY = game->pc->dir.x;
    game->pc->pos.x += rightX * 100;
    game->pc->pos.y += rightY * 100;
    update_img(game);
}

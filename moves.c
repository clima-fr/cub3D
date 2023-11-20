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

/* t_vd2D  update_pos2dir(t_general *game, bool mov)
{
    t_vd2D new_pos;
    double  speed;

    speed = 1;
    if(mov)
        speed = 100;
    new_pos.x = game->pc->pos.x + game->pc->dir.x * speed;
    new_pos.y = game->pc->pos.y + game->pc->dir.y * speed;
    return(new_pos);
}
 */



void reset_rad(t_player *pc)
{
    if(pc->ang < 0)
        pc->ang  += 2 * M_PI;
    else if(pc->ang  >= 2 * M_PI)
        pc->ang  -= 2 * M_PI;
}

void update_ang(t_player *pc, t_rot rot)
{
	if(rot == LEFT)
		pc->ang -= 0.1;
	else if(rot == RIGHT)
		pc->ang += 0.1;
    reset_rad(pc);
}

void update_pos(t_player *pc, t_mov mov)
{
	t_vd2D inv;
	t_vd2D tmp;

	set_vd2D(&inv, -(pc->dir.y), pc->dir.x);
	inv = mult_vd2D(&inv, 100);
	tmp = mult_vd2D(&pc->dir, 100);
	if(mov == W_FRONT)
				pc->pos = sum_vd2D(&pc->pos,&tmp);
	else if(mov == S_BACK)
		pc->pos = sub_vd2D(&pc->pos, &tmp);
	else if(mov == A_LEFT)
		pc->pos = sub_vd2D(&pc->pos, &inv);
	else if(mov == D_RIGHT)
		pc->pos = sum_vd2D(&pc->pos, &inv);
}

void update_dir(t_player *pc)
{
	t_vd2D ang;

	set_vd2D(&ang, (double)cos(pc->ang), (double)sin(pc->ang));
	pc->dir = mult_vd2D(&ang, 50);
}

void update_plane(t_player  *pc, int mov_type)
{
	if(mov_type == RIGHT)
		pc->plane = rot_vd2D(&pc->dir, M_PI/2);
	else if(mov_type == LEFT)
		pc->plane = rot_vd2D(&pc->dir, -M_PI/2);

}

void rotating(t_player *pc, t_rot type)
{
	update_ang(pc, type);
	update_dir(pc);
	update_plane(pc, type);
}

//----------------------------------------------------------------
/*

//ATUALIZAR VETORES: DIR(de acordo com ang)
//CAM_PLANE(de acordo com DIR)
void	move_fov_left(t_general *game)
{
	update_ang(game->pc, LEFT);
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

//ATUALIZAR VETORES: POS(de acordo com DIR)
void	move_w(t_general *game)
{
    game->pc->pos.x +=  game->pc->dir.x * 100;
    game->pc->pos.y +=  game->pc->dir.y * 100;
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
*/
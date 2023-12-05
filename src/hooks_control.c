/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:13:48 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 20:13:51 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_wall(char **map, t_vd2D *pos, t_vd2D *tmp, int dir)
{
	if (map[(int)(pos->y + VEL * tmp->y * dir)][(int)pos->x] == '0')
	{
		if (map[(int)pos->y][(int)(pos->x + VEL * tmp->x * dir)] == '0')
			return (true);
	}
	return (false);
}

void	sides(t_cub *game, t_vd2D *dir, int orient)
{
	t_math	*p;
	t_vd2D	temp;

	p = &game->player;
	temp.x = dir->x;
	temp.y = dir->y;
	rot_vd2d(&temp, PI / 2);
	if (check_wall(game->copy_map, &p->pos, &temp, orient))
	{
		p->pos.y += VEL * temp.y * orient;
		p->pos.x += VEL * temp.x * orient;
	}
	set_map_pos(p);
	rayscaster(game);
}

void	front_back(t_cub *game, t_vd2D *dir, int orient)
{
	t_math	*p;

	p = &game->player;
	if (check_wall(game->copy_map, &p->pos, &p->dir, orient))
	{
		p->pos.y += VEL * dir->y * orient;
		p->pos.x += VEL * dir->x * orient;
	}
	set_map_pos(p);
	rayscaster(game);
}

void	rot_player(t_cub *game, double angle)
{
	t_math	*p;

	p = &game->player;
	rot_vd2d(&p->dir, angle);
	rot_vd2d(&p->plane, angle);
	rayscaster(game);
}

int	hooks(int keypress, t_cub *game)
{
	if (keypress == XK_Escape)
		free_mlx(game);
	if (keypress == XK_w)
		front_back(game, &game->player.dir, FRONT);
	if (keypress == XK_s)
		front_back(game, &game->player.dir, BACK);
	if (keypress == XK_a)
		sides(game, &game->player.dir, LEFT);
	if (keypress == XK_d)
		sides(game, &game->player.dir, RIGHT);
	if (keypress == XK_Left)
		rot_player(game, -R_ANG);
	if (keypress == XK_Right)
		rot_player(game, R_ANG);
	return (0);
}

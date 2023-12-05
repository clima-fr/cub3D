/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:58:36 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 19:58:38 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_wall_coordinate(t_math *player)
{
	if (!player->hit_side)
	{
		if (player->pos.x < player->map_pos.x)
			player->coordinate_wall = V_WE;
		else
			player->coordinate_wall = V_EA;
	}
	else
	{
		if (player->pos.y > player->map_pos.y)
			player->coordinate_wall = H_NO;
		else
			player->coordinate_wall = H_SO;
	}
}

void	set_height(t_cub *game)
{
	t_math	*p;

	p = &game->player;
	p->wall_h = fabs(((double)game->win_h / p->perp));
	p->wall_b = (game->win_h / 2.00) - (p->wall_h / 2.00);
	p->wall_e = (game->win_h / 2.00) + (p->wall_h / 2.00);
	if (p->wall_b < 0)
		p->wall_b = 0;
	if (p->wall_e > game->win_h)
		p->wall_e = game->win_h -1;
}

void	set_perp(t_cub *g)
{
	t_math	*p;

	p = &g->player;
	if (p->hit_side == 0)
	{
		p->perp = fabs(p->map_pos.x - p->pos.x + ((1 - p->step_dda.x) / 2));
		p->perp /= p->ray_dir.x;
	}
	else
	{
		p->perp = fabs(p->map_pos.y - p->pos.y + ((1 - p->step_dda.y) / 2));
		p->perp /= p->ray_dir.y;
	}
}

void	raycasting(t_cub *g)
{
	set_perp(g);
	set_height(g);
	set_wall_coordinate(&g->player);
	get_hit_point_tex_x(&g->player);
	set_point_tex_y(g);
	render_wall(g);
}

int	rayscaster(t_cub *g)
{
	canvas(g, CREATE);
	while (g->pixel < g->win_w)
	{
		dda(g);
		raycasting(g);
		g->pixel++;
	}
	canvas(g, UPDATE);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:53:06 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 19:53:09 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_ray(t_cub *g)
{
	double		mult;
	t_vd2D		cam_pixel;

	mult = 2 * ((double)g->pixel / (g->win_w - 1)) - 1;
	cam_pixel = mult_vd2d(&g->player.plane, mult);
	g->player.ray_dir = sum_vd2d(&g->player.dir, &cam_pixel);
	set_map_pos(&g->player);
}

void	set_delta(t_cub *g)
{
	if (g->player.ray_dir.x == 0)
		g->player.delta.x = 1e30;
	else
		g->player.delta.x = fabs(1 / g->player.ray_dir.x);
	if (g->player.ray_dir.y == 0)
		g->player.delta.y = 1e30;
	else
		g->player.delta.y = fabs(1 / g->player.ray_dir.y);
}

void	set_dist2side(t_cub *g)
{
	if (g->player.ray_dir.x < 0)
	{
		g->player.d2s.x = g->player.pos.x - g->player.map_pos.x;
		g->player.d2s.x *= g->player.delta.x;
		g->player.step_dda.x = -1;
	}
	else
	{
		g->player.d2s.x = g->player.map_pos.x + 1.0 - g->player.pos.x;
		g->player.d2s.x *= g->player.delta.x;
		g->player.step_dda.x = 1;
	}
	if (g->player.ray_dir.y < 0)
	{
		g->player.d2s.y = g->player.pos.y - g->player.map_pos.y;
		g->player.d2s.y *= g->player.delta.y;
		g->player.step_dda.y = -1;
	}
	else
	{
		g->player.d2s.y = g->player.map_pos.y + 1.0 - g->player.pos.y;
		g->player.d2s.y *= g->player.delta.y;
		g->player.step_dda.y = 1;
	}
}

void	run_dda(t_cub *g)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (g->player.d2s.x < g->player.d2s.y)
		{
			g->player.d2s.x += g->player.delta.x;
			g->player.map_pos.x += g->player.step_dda.x;
			g->player.hit_side = 0;
		}
		else
		{
			g->player.d2s.y += g->player.delta.y;
			g->player.map_pos.y += g->player.step_dda.y;
			g->player.hit_side = 1;
		}
		if (g->copy_map[g->player.map_pos.y][g->player.map_pos.x] == '1')
			hit = true;
	}
}

void	dda(t_cub *g)
{
	set_ray(g);
	set_delta(g);
	set_dist2side(g);
	run_dda(g);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:09:00 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 20:09:03 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_hit_point_tex_x(t_math *player)
{
	double	wall;
	int		t_wall;

	t_wall = player->coordinate_wall;
	wall = 0;
	if (t_wall == V_WE)
		wall = player->pos.y + player->perp * player->ray_dir.y;
	else if (t_wall == V_EA)
		wall = player->pos.y - player->perp * player->ray_dir.y;
	else if (t_wall == H_NO)
		wall = player->pos.x - player->perp * player->ray_dir.x;
	else if (t_wall == H_SO)
		wall = player->pos.x + player->perp * player->ray_dir.x;
	wall -= floor(wall);
	player->px_tex.x = (int)(wall * (double)SIZE);
	if (t_wall == H_SO || t_wall == V_EA)
		player->px_tex.x = SIZE - player->px_tex.x - 1;
}

void	set_point_tex_y(t_cub *g)
{
	g->player.step_render = fabs((double)SIZE / g->player.wall_h);
	g->player.pos_render = (g->player.wall_b - (g->win_h / 2) \
		+ (g->player.wall_h / 2)) * g->player.step_render;
}

void	render_wall(t_cub *g)
{
	int		canv_x;
	int		canv_y;
	double	pos;
	double	step;

	canv_y = g->player.wall_b;
	canv_x = g->pixel;
	pos = g->player.pos_render;
	step = g->player.step_render;
	while (canv_y < g->player.wall_e && canv_y < g->win_h)
	{
		g->player.px_tex.y = (int)pos & (SIZE - 1);
		pos += step;
		my_mlx_pixel_put(g, canv_x, canv_y, coordinate_tex(g));
		canv_y++;
	}
}

int	coordinate_tex(t_cub *g)
{
	int	x;
	int	y;
	int	t_wall;

	x = g->player.px_tex.x;
	y = g->player.px_tex.y;
	t_wall = g->player.coordinate_wall;
	if (t_wall == V_WE)
		return (my_mlx_pixel_get(&g->ea_tex, x, y));
	else if (t_wall == V_EA)
		return (my_mlx_pixel_get(&g->we_tex, x, y));
	else if (t_wall == H_NO)
		return (my_mlx_pixel_get(&g->no_tex, x, y));
	else
		return (my_mlx_pixel_get(&g->so_tex, x, y));
}

int	render_horizont(t_cub *g, int bx, int by)
{
	int	mid;
	int	color;

	mid = 1;
	color = g->floor;
	if (by == 0)
	{
		mid = 2;
		color = g->ceiling;
	}
	while (by < g->win_h / mid)
	{
		bx = 0;
		while (bx < g->win_w)
		{
			my_mlx_pixel_put(g, bx, by, color);
			bx++;
		}
		by++;
	}
	return (0);
}

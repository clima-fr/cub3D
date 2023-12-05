/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:25:14 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 20:25:19 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_textures(t_cub *g, int size)
{
	load_tex_xpm(g, &g->no_tex, g->n, size);
	load_tex_xpm(g, &g->so_tex, g->s, size);
	load_tex_xpm(g, &g->ea_tex, g->e, size);
	load_tex_xpm(g, &g->we_tex, g->w, size);
	load_tex_addr(g, &g->no_tex);
	load_tex_addr(g, &g->so_tex);
	load_tex_addr(g, &g->ea_tex);
	load_tex_addr(g, &g->we_tex);
}

void	set_look(t_cub *g)
{
	if (g->start == 'N')
	{
		set_vd2d(&g->player.dir, 0, -1);
		set_vd2d(&g->player.plane, 0.66, 0);
	}
	else if (g->start == 'S')
	{
		set_vd2d(&g->player.dir, 0, 1);
		set_vd2d(&g->player.plane, -0.66, 0);
	}
	else if (g->start == 'E')
	{
		set_vd2d(&g->player.dir, 1, 0);
		set_vd2d(&g->player.plane, 0, 0.66);
	}
	else if (g->start == 'W')
	{
		set_vd2d(&g->player.dir, -1, 0);
		set_vd2d(&g->player.plane, 0, -0.66);
	}
}

void	set_first_pos(t_cub *g, int i, int j)
{
	while (g->copy_map[++i])
	{
		j = -1;
		while (g->copy_map[i][++j])
		{
			if (g->copy_map[i][j] == g->start)
			{
				g->player.pos.x = j + 0.5;
				g->player.pos.y = i + 0.5;
				g->copy_map[i][j] = '0';
				set_look(g);
				return ;
			}
		}
	}
}

int	init_render(t_cub *g)
{
	g->mlx = mlx_init();
	g->win_h = 1080;
	g->win_w = 1920;
	g->win = mlx_new_window(g->mlx, g->win_w, g->win_h, "Cliva:The_Last_of_Us");
	init_textures(g, SIZE);
	rayscaster(g);
	return (0);
}

int	run_game(t_cub *g)
{
	init_render(g);
	mlx_key_hook(g->win, hooks, g);
	mlx_hook(g->win, 17, 1L << 0, free_mlx, g);
	mlx_loop(g->mlx);
	return (0);
}

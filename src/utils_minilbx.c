/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minilbx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:06:22 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 20:06:27 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	my_mlx_pixel_get(t_tex *img, int point_x, int point_y)
{
	return (*(int *)(img->addr + (point_y * img->line_len + point_x * \
					(img->bpp / 8))));
}

void	my_mlx_pixel_put(t_cub *g, int x, int y, int color)
{
	char	*dst;

	dst = g->canvas.addr + (y * g->canvas.line_len + x \
		* (g->canvas.bpp / 8));
	*(unsigned int *)dst = color;
}

void	canvas(t_cub *g, int flag)
{
	if (flag == CREATE)
	{
		if (g->canvas.img)
			mlx_destroy_image(g->mlx, g->canvas.img);
		g->canvas.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
		g->canvas.addr = mlx_get_data_addr(g->canvas.img, \
		&g->canvas.bpp, &g->canvas.line_len, \
		&g->canvas.endian);
		render_horizont(g, 0, 0);
		render_horizont(g, 0, g->win_h / 2);
	}
	else if (flag == UPDATE)
	{
		mlx_clear_window(g->mlx, g->win);
		mlx_put_image_to_window(g->mlx, g->win, g->canvas.img, 0, 0);
		g->pixel = 0;
	}
}

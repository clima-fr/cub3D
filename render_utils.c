/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:13:17 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/25 19:13:19 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//guarda imagem a ser renderizada em um BUFFER para printar tudo de uma vez
void	img_pix_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_img + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/* void draw_line_with_stroke(t_general *game, t_vd2D bg, t_vd2D end, int color)
{
    int stroke_width = 2;
    int dx = abs((int)end.x - (int)bg.x);
    int dy = abs((int)end.y - (int)bg.y);
    int sx = (int)bg.x < (int)end.x ? 1 : -1;
    int sy = (int)bg.y < (int)end.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        img_pix_put(game->render, (int)bg.x, (int)bg.y, color);
        img_pix_put(game->render, (int)bg.x + sx, (int)bg.y + sy, color);

        if ((int)bg.x == (int)end.x && (int)bg.y == (int)end.y)
            break;

        for (int i = 0; i < stroke_width; i++)
        {
            img_pix_put(game->render, (int)bg.x + sx, (int)bg.y + sy + i, color);
            img_pix_put(game->render, (int)bg.x + sx + i, (int)bg.y + sy, color);
        }

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            bg.x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            bg.y += sy;
        }
    }
} */

 void print_ray(t_general *game, t_vd2D bg, t_vd2D end, int color)
{
    int dx = abs((int)end.x - (int)bg.x);
    int dy = abs((int)end.y - (int)bg.y);
    int sx = (int)bg.x  < (int)end.x ? 1 : -1;
    int sy = (int)bg.y <  (int)end.y? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) 
    {
        img_pix_put(game->render, (int)bg.x, (int)bg.y, color);
        if ((int)bg.x == (int)end.x && (int)bg.y == (int)end.y)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            bg.x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            bg.y += sy;
        }
    }
}


//desenha o teto e o piso ao mesmo tempo
void draw_horizont(t_general *game, int bx, int by, int color) 
{
    int divisor;

    divisor = 1;
    if(by == 0)
        divisor = 2;
    while(by < game->render->win_height / divisor)
    {
        bx = 0;
        while(bx < game->render->win_width)
        {
            img_pix_put(game->render, bx, by, color);
            bx++;
        }
        by++;
    }
}

void	create_buffer_img(t_general *game)
{
	game->render->img = mlx_new_image(game->render->mlx, game->render->win_width , game->render->win_height);
	game->render->addr_img = mlx_get_data_addr(game->render->img, &game->render->bits_per_pixel, &game->render->line_length, &game->render->endian);
    draw_horizont(game, 0, 0, 0xFFFFFF);
    draw_horizont(game, 0, game->render->win_height / 2, 0x646464);
    raycaster(game);
    mlx_put_image_to_window(game->render->mlx, game->render->win, game->render->img, 0, 0);
}
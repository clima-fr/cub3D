/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:38:31 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/06 18:38:32 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*recebe: vetor de direcao do ray com mag max de 1, e calcula o 
valor da hipotenusa do triangulo formado pelos catetos/vetores dir*/
double get_hypo(t_vd2D *cat)
{
    return (sqrt(cat->x * cat->x + cat->y * cat->y));
}

/*recebe: vetores dir com mag max de 1, e calcula 
as distancias entre as linhas verticais e horizontais
de acordo com o angulo de dir do ray*/
t_vd2D set_delta(t_vd2D *dir)
{
    t_vd2D delta;

    delta.x = fabs(CELL_SIZE * get_hypo(dir)) / dir->x;
    delta.y = fabs(CELL_SIZE * get_hypo(dir)) / dir->y;

    return (delta);
}

/*recebe: posicao exata do player e
calcula o quadrante da sua posicao no mapa*/
t_vi2D  set_map(t_vd2D *pos)
{
    t_vi2D map;

    map.x = (int)floor(pos->x);
    map.y = (int)floor(pos->y);

    return (map);
}

/*recebe: posicao exata do player, mapeamento do quadrante do player,
direcao do ray, e valor da distancia entre linhas verticais e horizontais(aka delta)
e calcula a distancia inicial do player para as primeiras linhas horizontais(y) e verticais(x)*/
t_vd2D  set_dist2side(t_vd2D *pos, t_vi2D *map, t_vd2D *dir, t_vd2D *delta)
{
    t_vd2D dist;
    t_vd2D step;

    /*se o dir.x for negativo, o fov esta voltado para esquerda do mapa, o calculo DDA decrementará o x
    se o dir.x for maior que zero, o fov esta voltado para direita do mapa
    e o calculo DDA incrementará o x*/
    if(dir->x < 0)
    {
        dist.x = (pos->x - map->x) * delta->x;
        step.x = -1;
    }
    else
    {
        dist.x = ((map->x + CELL_SIZE)  - pos->x) * delta->x;
        step.x = 1;
    }
    /*se o dir.y for negativo, o fov esta voltado para cima do mapa, o calculo DDA decrementará o y
    se o dir.y for maior que zero, o fov esta voltado baixo do mapa
    e o calculo DDA incrementará o y*/
    if(dir->y < 0)
    {
        dist.y = (pos->y - map->y) * delta->y;
        step.y = -1;
    }
    else
    {
        dist.y = ((map->y + CELL_SIZE)  - pos->y) * delta->y;
        step = 1;
    }
}

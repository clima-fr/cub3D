/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_update1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:16:00 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/25 19:16:02 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//FUNCAO TEMPORARIA, ALTERAR PARA AUTOMATICO
void fill_map(t_player *pc)
{
    for(int i = 0; i < 10; i++) 
    {
        if(i == 0 || i == 9)
            strcpy(pc->tmp_map[i], "1111111111"); 
		else if(i == 1 || i == 8 || i == 2 || i == 7)
            strcpy(pc->tmp_map[i], "1000000001");  
        else
            strcpy(pc->tmp_map[i], "1000110001");  
    }
}

/* 	0123456789

0	1111111111
1	1000000001
2	10P0000001
3	1000110001
4	1000110001
5	1000110001
6	1000110001
7	1000000001
8	1000000001
9	1111111111 */

//FUNCAO TEMPORARIA, ALTERAR PARA AUTOMATICO
/* void	get_pc(t_general *game)
{
	if(!game->pc->pos.x || !game->pc->pos.y)
	{
		//posicionamento do player, temporariamente no centro da tela
		game->pc->pos.x = 164;
		game->pc->pos.y = 164;
	}
	//else
		//update_player_pos(player);
} */
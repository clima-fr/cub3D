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
void fill_map(t_general *game)
{
    for(int i = 0; i < 10; i++) 
    {
        if(i == 0 || i == 9)
            strcpy(game->pc->tmp_map[i], "1111111111");  
        else
            strcpy(game->pc->tmp_map[i], "1000000001");  
    }
}

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
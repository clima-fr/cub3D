/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:18:38 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/25 19:18:39 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//tratar eventos na window de botao X
int	handler_win(int key, t_general *game)
{
    (void)key;
    finish_game(game);
	return (0);
}

//tratar eventos de clique no teclado
int handler_press(int key, t_general *game)
{
	if(key == XK_Escape)
		handler_win(key, game);
    else
    {
    	printf("HOI, CLARINHA NEAH?!");
        printf("KEY: %d\n", key);
        check_key_movs(key, game);
    }
    return(0);
}

void    check_key_movs(int key, t_general *game)
{
  	if (key == XK_Left)
		move_fov_left(game);
    else if(key == XK_Right)
        move_fov_right(game);
    else if (key == XK_w)
        move_w(game);
	else if (key == XK_s)
		move_s(game);
	else if (key == XK_a)
		move_a(game);
	else if (key == XK_d)
		move_d(game);
}

void    check_hooks(t_general	*game)
{
    //tratar eventos na window de botao X
	mlx_hook(game->render->win, 17, 1L<<0, handler_win, game);
	
	//tratar eventos de clique no teclado
	mlx_key_hook(game->render->win, handler_press, game);
}
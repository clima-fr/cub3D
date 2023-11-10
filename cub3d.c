/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <ivbatist@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:50:06 by ivbatist          #+#    #+#             */
/*   Updated: 2023/10/17 18:56:17 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//#include "structs.h"

void init_game(t_general	*game)
{
	//iniciar estruturas dentro da general
	game->render = malloc(sizeof(t_mlx));
    game->pc = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_raycaster));

	//retornar mensagem de erro
	if(!game->pc || !game->render || !game->render)
	{
		write(1,"struct malloc error\n", 4);
		exit(1);
	}

	//ALTERAR PARA AUTOMATICO: armazana o mapa na memoria do jogo
	fill_map(game);

	//ALTERAR PARA AUTOMATICO: configuracao do tamanho da  janela do jogo
	game->render->win_width = 320;
	game->render->win_height = 200;

	//ALTERAR PARA AUTOMATICO: configura angulo e vetor de rotacao do player
	game->pc->ang = degree_to_radians(45);
	init_vd2D(&game->pc->dir, cos(game->pc->ang), sin(game->pc->ang));

	//ALTERAR PARA AUTOMATICO: Configura o vetor de plane
	init_vd2D(&game->pc->plane, 0.66, 0);
	
	//ALTERAR PARA AUTOMATICO: Configura o vetor de posicao inicial
	init_vd2D(&game->pc->pos, 160, 100);
	//init_vd2D(&game->pc->map_pos, 160, 100);

	//iniciar janela
	game->render->mlx = mlx_init();
	game->render->win = mlx_new_window(game->render->mlx, game->render->win_width, game->render->win_height, "ba_tits");

}


//roda a sequencia do jogo
void	run_game(t_general	*game)
{
	//verifica entradas por teclado
	check_hooks(game);
	
	//loop para exibicao da janela
	mlx_loop(game->render->mlx);	
}

int	main()
{
	t_general game;

	//FUNCAO PARA VERIFICAR OS ARGS
	//FUNCAO PARA VERIFICAR O MAPA

	init_game(&game);
	create_buffer_img(&game);
	mlx_loop(&(game.render->mlx));	
	//run_game(&game);

}


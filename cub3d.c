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

void init_pc(t_player *pc)
{
	//ALTERAR PARA AUTOMATICO: armazana o mapa na memoria do jogo
	fill_map(pc);
	//print_array(pc->tmp_map);

	//ALTERAR PARA AUTOMATICO: configura angulo e vetor de rotacao do player
	pc->ang = degree_to_radians(90);
	set_vd2D(&pc->dir, cos(pc->ang), sin(pc->ang));

	//ALTERAR PARA AUTOMATICO: Configura o vetor de plane
	set_vd2D(&pc->plane, 0.66, 0);
	
	//ALTERAR PARA AUTOMATICO: Configura o vetor de posicao inicial
	set_vd2D(&pc->pos, 2.5, 2.5);
	pc->map_pos.x = (int)2;
	pc->map_pos.y = (int)2;
}

void init_render(t_mlx *render)
{
	//ALTERAR PARA AUTOMATICO: configuracao do tamanho da  janela do jogo
	render->win_width = 320;
	render->win_height = 200;

	//iniciar janela
	render->mlx = mlx_init();
	render->win = mlx_new_window(render->mlx, render->win_width, render->win_height, "ba_tits");
}

void init_raycaster(t_raycaster *ray)
{
	init_vd2D(&ray->cam_pixel);
	init_vd2D(&ray->dir);
	init_vd2D(&ray->delta);
	init_vd2D(&ray->dist2side);
	init_vi2D(&ray->step);
	init_vd2D(&ray->dda_line);
	init_vi2D(&ray->map_hit);
	init_vd2D(&ray->wall_line);
}

void init_game(t_general	*game)
{
	//iniciar estruturas dentro da general
	game->render = malloc(sizeof(t_mlx));
    game->pc = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_raycaster));

	//retornar mensagem de erro
	//AJUSTAR PARA ENDERECO E CONTEUDO
	if(!game->pc || !game->render || !game->render)
	{
		write(1,"struct malloc error\n", 4);
		exit(1);
	}
	init_pc(game->pc);
	init_render(game->render);
	init_raycaster(game->ray);

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
	raycaster(&game);
	run_game(&game);

}


#include "cub3d.h"

void print_vd(t_vd2D *this, char *name)
{
    printf("[%s vector]\n", name);
    printf("[X] -> %f\n", this->x);
    printf("[Y] -> %f\n", this->y);
}

void print_vd2(t_vi2D *this, char *name)
{
    printf("[%s vector]\n", name);
    printf("[X] -> %d\n", this->x);
    printf("[Y] -> %d\n", this->y);
}

void set_perp(t_general *game)
{
    if(game->ray->hit_side == FACE_W_E)
    {
        game->ray->perp_dist = fabs(game->ray->map_hit.x - game->pc->pos.x + ((1 - game->ray->step.x) / 2));
        game->ray->perp_dist /= game->ray->dir.x;
    }
    else
    {
        game->ray->perp_dist = fabs(game->ray->map_hit.y - game->pc->pos.y + ((1 - game->ray->step.y) / 2));
        game->ray->perp_dist /= game->ray->dir.y;
    }
    printf("[perp_dist]\n[int] -> %f\n\n", game->ray->perp_dist);
}

void    dda(t_general *game)
{
    bool hit;

    hit = false;

    /*talvez nao precise fazer a copia ja que ambos vetores sao
    usados para o dda apenas*/

    copy_vd2D(&game->ray->dda_line, &game->ray->dist2side);
    //print_vd(&game->ray->dda_line, "RAY_dda_line");

    copy_vi2D(&game->ray->map_hit, &game->pc->map_pos);
    //print_vd2(&game->ray->map_hit, "RAY_hit_side");

    while(!hit)
    {
        if(game->ray->dda_line.x < game->ray->dda_line.y)
        {
            game->ray->dda_line.x += game->ray->delta.x;
            game->ray->map_hit.x += game->ray->step.x;
            game->ray->hit_side = FACE_W_E;
        }
        else
        {
            game->ray->dda_line.y += game->ray->delta.y;
            game->ray->map_hit.y += game->ray->step.y;
            game->ray->hit_side = FACE_N_S;
        }
        if(game->pc->tmp_map[game->ray->map_hit.x][game->ray->map_hit.y] == '1')
            hit = true;
    }
    //print_vd(&game->ray->dda_line, "RAY_dda_line");
    //print_vd2(&game->ray->dda_line, "RAY_hit_side");
}

double calc_d2s(t_general *game, bool x, bool negatv)
{
    if(x && negatv)
        return (game->pc->pos.x - game->pc->map_pos.x) * game->ray->delta.x;
    else if(x && !negatv)
        return (game->pc->map_pos.x + 1 - game->pc->pos.x) * game->ray->delta.x;
    else if(!x && negatv)
        return (game->pc->pos.y - game->pc->map_pos.y) * game->ray->delta.y;
    else if(!x && !negatv)
        return (game->pc->map_pos.y + 1 - game->pc->pos.y) * game->ray->delta.y;
}

void set_dda(t_general *game)
{
    game->ray->delta.x = fabs(1 / game->ray->dir.x);
    game->ray->delta.y = fabs(1 / game->ray->dir.y); 
    //print_vd(&game->ray->delta, "RAY_delta");
    
    if(game->ray->dir.x < 0)
    {
        game->ray->dist2side.x = calc_d2s(game, true, true);
        game->ray->step.x = CK_LEFT;
    }
    else
    {
        game->ray->dist2side.x = calc_d2s(game, true, false);
        game->ray->step.x = CK_RIGHT;
    }
    if(game->ray->dir.y < 0)
    {
        game->ray->dist2side.y = calc_d2s(game, false, true);
        game->ray->step.y = CK_TOP;

    }
    else
    {
        game->ray->dist2side.y = calc_d2s(game, false, false);
        game->ray->step.y = CK_DOWN;
    }
    //print_vd(&game->ray->dist2side, "RAY_dist2side");
    //print_vd2(&game->ray->step, "RAY_step");
}

void set_ray(t_general *game)
{        
    double mult;
    t_vd2D cam_pixel;

    mult = (2 * game->ray->pixel/game->render->win_width) - 1;
    //printf("[mult]\n[int] -> %f\n\n", mult);
    
    cam_pixel = mult_vd2D(&game->pc->plane, mult);
    //print_vd(&game->ray->cam_pixel, "cam_pixel");

    game->ray->dir = sum_vd2D(&game->pc->dir, &cam_pixel); 
    //print_vd(&game->ray->dir, "RAY_dir");

}

//-----------------------------------------------------------------------------------------------

void  raycaster(t_general *game)
{
    update_img(game);
	while (game->ray->pixel < game->render->win_width)
	{
		//ATUALIZAR O MAP_POS JUNTO COM O POS DO PLAYER, OU USAR ELE NO LUGAR DO MAP_HIT E ATUALIZAR AQUI
		
        /* print_vd(&game->pc->pos, "PC_pos");
        print_vd(&game->pc->plane, "PC_plane");
        print_vd(&game->pc->dir, "PC_dir");
        print_vd2(&game->pc->map_pos, "PC_mappos"); */

        set_ray(game);
		dda(game);
        set_perp(game);

        //calcular as alturas
        //calcular os pixels em colunas
		game->ray->pixel++;
	}
	mlx_clear_window(game->render->mlx, game->render->win);
    mlx_put_image_to_window(game->render->mlx, game->render->win, game->render->img, 0, 0);
	game->ray->pixel = 0;
	
    //VERIFICAR NECESSIDADE DE RETORNO AO FIM
    //return (0);

//-----------------------------------------------------------------------

        //calcula a altura da linha que representa a parede e o comeco e o fim dela
        game->ray->wall_height_pixel = game->render->win_height / game->ray->perp_dist;
        printf("[wall_height_pixel]\n[int] -> %f\n\n", game->ray->wall_height_pixel);

        double line_b_Y = game->render->win_height / 2 - game->ray->wall_height_pixel/2;
        double line_e_Y = game->render->win_height / 2 + game->ray->wall_height_pixel/2;

        set_vd2D(&game->ray->wall_line, line_b_Y, line_e_Y);
        print_vd(&game->ray->wall_line, "wall_line");
        
        
        //escolhe textura pelo tipo da parede
        int c;

        c = 0x0000FFFF;
        if(!game->ray->hit_side)
            c = 0x0000FF00;

        t_vd2D wall_b;
        t_vd2D wall_e;

        set_vd2D(&wall_b, game->ray->pixel, game->ray->wall_line.x);
        set_vd2D(&wall_e, game->ray->pixel, game->ray->wall_line.y + 1);
        print_vd(&wall_b, "wall_b");
        print_vd(&wall_e, "wall_e");

}

/*calculos:

WIDTH : STANDARD
HEIGHT : STANDARD
POS : MAPA
PC_DIR : MAPA
PLANE : STANDARD
MAP_POS : MAPA

LOOP() -> pixel
multi <- pixel
cam_pixel <- pixel/ multi/ width
RAY_DIR <- cam_pixel / PC_DIR

DELTA <- RAY_DIR **verificar se ha problema no calculo de ray_dir em 0
D2S <- RAY_DIR / PC_POS / MAP_POS -> step

DDA()
dda_line* <- D2S / DELTA / map_hit* / MAP / step -> hit_side

(**)dda_line e map_hit podem ser substituidos respectivamente por
    d2s e map_pos */



/*CALCULO PARA EVITAR VALORES DIVIDOS POR 0, MAS 
ATE ENTAO ESTAVA DANDO ERRADO, POR ISSO IGNORAR*/

/*
if((int)game->ray->dir.x == 0)
    set_vd2D(&game->ray->delta, 1, 0);
else
{
    if((int)game->ray->dir.y)
        game->ray->delta.x = fabs(1/game->ray->dir.x);
}
if((int)game->ray->dir.y == 0)
    set_vd2D(&game->ray->delta, 0, 1);
else
{
    if((int)game->ray->dir.x)
        game->ray->delta.y = fabs(1/game->ray->dir.y);
}*/
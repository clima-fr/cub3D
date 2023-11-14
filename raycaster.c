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

void  raycaster(t_general *game)
{
    game->ray->pixel = 0;
    while(game->ray->pixel < game->render->win_width)
    {
        double mult;
        bool    hit;

        //verificando valores iníciais de vetores
        //print_vd(&game->pc->pos, "pc_pos");
        //print_vd(&game->pc->plane, "pc_plane");
        //print_vd(&game->pc->dir, "pc_dir");
        //print_vd2(&game->pc->map_pos, "pc_mappos");


        hit = false;
        mult = (2 * game->ray->pixel/game->render->win_width) - 1;
        printf("[mult]\n[int] -> %f\n\n", mult);
        
        //define quanto do angulo de visao sera impresso por 1 linha vertical de pixel
        mult_vd2D(&game->ray->cam_pixel, &game->pc->plane, mult);
        //print_vd(&game->ray->cam_pixel, "cam_pixel");

        //define vetor final do angulo de visao
        sum_vd2D(&game->ray->dir, &game->pc->dir, &game->ray->cam_pixel); 
        print_vd(&game->ray->dir, "ray_dir");

        print_vd(&game->ray->delta, "ray_delta");
        //define deltas para pular de cubo em cubo no dda, com consideracao de infinito

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
        }//verificar se ray->dir foi atribuído corretamente anteriormente 
        print_vd(&game->ray->delta, "ray_delta");

        //define distancia do player ate as linhas cartinais mais proximas
        if((int)game->ray->dir.x < 0)
        {
            game->ray->dist2side.x = (game->pc->pos.x - game->pc->map_pos.x) * game->ray->delta.x;
            game->ray->step.x = -1;//verificar resultado dessa operação é double ou int
        }
        else
        {
            game->ray->dist2side.x = (game->pc->map_pos.x + 1 - game->pc->pos.x) * game->ray->delta.x;
            game->ray->step.x = 1;
        }
        if((int)game->ray->dir.y < 0)
        {
            game->ray->dist2side.y = (game->pc->pos.y - game->pc->map_pos.y) * game->ray->delta.y;
            game->ray->step.y = -1;

        }
        else
        {
            game->ray->dist2side.y = (game->pc->map_pos.y + 1 - game->pc->pos.y) * game->ray->delta.y;
            game->ray->step.y = 1;
        }
        print_vd(&game->ray->dist2side, "dist2side");
        print_vd2(&game->ray->step, "step");

        //funcao DDA
        copy_vd2D(&game->ray->dda_line, &game->ray->dist2side);
        print_vd(&game->ray->dda_line, "dda_line");
        
        print_vd2(&game->pc->map_pos, "pc_mappos");
        //ALTERAR PARA COPIAR O FLOOR() de x e y de PC->POS
        set(&game->ray->map_hit, floor(game->pc->map_pos.x), floor(game->pc->map_pos.y));
        /*copy_vi2D(&game->ray->map_hit, &game->pc->map_pos);*/
        print_vd2(&game->ray->map_hit, "map_cub_hit");

        while(hit == false)
        {
            if(game->ray->dda_line.x < game->ray->dda_line.y)
            {
                game->ray->map_hit.x += game->ray->step.x;
                game->ray->dda_line.x += game->ray->delta.x;
                game->ray->hit_side = 0;
            }
            else
            {
                game->ray->map_hit.y += game->ray->step.y;
                game->ray->dda_line.y += game->ray->delta.y;
                game->ray->hit_side = 1;
            }
            if(game->pc->tmp_map[game->ray->map_hit.x][game->ray->map_hit.y] == '1')
                hit = true;
            print_vd2(&game->ray->map_hit, "map_hit");
        }
        //fim de funcao DDA

        //verificacao de qual o tipo de parede que bateu
        if(!game->ray->hit_side)
            game->ray->perp_dist = fabs(game->ray->map_hit.x - game->pc->pos.x + (1 - game->ray->step.x) / 2) / game->ray->dir.x);
        else    
            game->ray->perp_dist = fabs(game->ray->map_hit.y - game->pc->pos.y + (1 - game->ray->step.y) / 2) / game->ray->dir.y;

        printf("[perp_dist]\n[int] -> %f\n\n", game->ray->perp_dist);

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

        /*if(game->ray->pixel == 159 || game->ray->pixel == 0 || game->ray->pixel == 319 || game->ray->pixel == 80 || game->ray->pixel == 240)*/
        
            print_ray(game, wall_b, wall_e, c);

        game->ray->pixel++;

    }
}

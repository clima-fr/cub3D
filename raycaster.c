#include "cub3d.h"

void print_vd(t_vd2D *this, char *name)
{
    printf("[%s vector]\n", name);
    printf("[X] -> %f\n", this->x);
    printf("[Y] -> %f\n", this->y);
}

void  raycaster(t_general *game)
{
    int pixel;

    pixel = 0;
    while(pixel < game->render->win_width)
    {
        double mult;
        bool    hit;
        //verificando valores iníciais de vetores
        print_vd(&game->pc->pos, "pc_pos");
        print_vd(&game->pc->plane, "plane");
        

        hit = false;
        mult = 2 * (pixel/game->render->win_width) - 1;
        
        //define quanto do angulo de visao sera impresso por 1 linha vertical de pixel
        game->ray->cam_pixel = mult_vd2D(&game->pc->plane, mult);
//verificar resultado de função, tentar passar qualquer número no lugar de mult e ver cam_pixel antes e depois

        //define vetor final do angulo de visao
        game->ray->dir = sum_vd2D(&game->pc->dir, &game->ray->cam_pixel);//verificar resultado da função, verificar valor de dor e de cam_pixel antes e depois da função 

        print_vd(&game->ray->cam_pixel, "cam_pixel");
        print_vd(&game->ray->dir, "ray_dir");


        //define deltas para pular de cubo em cubo no dda, com consideracao de infinito
        if(game->ray->dir.x == 0)
            init_vd2D(&game->ray->delta, 1, 0);
        else
        {
            if(game->ray->dir.y)
                game->ray->delta.x = fabs(1/game->ray->dir.x);
        }
        if(game->ray->dir.y == 0)
            init_vd2D(&game->ray->delta, 0, 1);
        else
        {
            if(game->ray->dir.x)
                game->ray->delta.y = fabs(1/game->ray->dir.y);
        }//verificar se ray->dir foi atribuído corretamente anteriormente 

        print_vd(&game->ray->delta, "ray_delta");

        //define distancia do player ate as linhas cartinais mais proximas
        if(game->ray->dir.x < 0)
        {
            game->ray->dist2side.x = (game->pc->pos.x - game->pc->map_pos.x) * game->ray->delta.x;
            game->ray->step.x = -1;//verificar resultado dessa operação é double ou int
        }
        else
        {
            game->ray->dist2side.x = (game->pc->map_pos.x + 1 - game->pc->pos.x) * game->ray->delta.x;
            game->ray->step.x = 1;
        }
        if(game->ray->dir.y < 0)
        {
            game->ray->dist2side.y = (game->pc->pos.y - game->pc->map_pos.y) * game->ray->delta.y;
            game->ray->step.y = -1;

        }
        else
        {
            game->ray->dist2side.y = (game->pc->map_pos.y + 1 - game->pc->pos.y) * game->ray->delta.y;
            game->ray->step.x = 1;
        }

        print_vd(&game->ray->dist2side, "dist2sizes");

        //funcao DDA
        game->ray->dda_line = copy_vd2D(&game->ray->dda_line, &game->ray->dist2side);//verificar se a função copy funciona corretamentente
        
        print_vd(&game->ray->dda_line, "dda_line");
        
        
        game->ray->map_hit = copy_vd2D(&game->ray->map_hit, (t_vd2D *)&game->pc->map_pos);
        //verificar conversão de vi2D pra vd2D
        
        print_vd(game->ray->map_hit, "map_cub_hit");

        while(!hit)
        {
            if(game->ray->dda_line.x < game->ray->dda_line.y)
            {
                game->ray->map_hit.x += game->ray->step.x;
                game->ray->dda_line.x += game->ray->delta.x;
                game->ray->hit_side = 0;
            print_vd(game->ray->map_hit, "map_cub_hit");
            }
            else
            {
                game->ray->map_hit.y += game->ray->step.y;
                game->ray->dda_line.y += game->ray->delta.y;
                game->ray->hit_side = 1;
            }
            if(game->pc->tmp_map[game->pc->map_pos.x][game->pc->map_pos.y] == 1)
                hit = true;
    
        }
        //fim de funcao DDA

        //verificacao de qual o tipo de parede que bateu
        if(!game->ray->hit_side)
            game->ray->perp_dist = fabs(game->ray->map_hit.x - game->pc->pos.x + ((1 - game->ray->step.x) / 2) / game->ray->dir.x);
        else    
            game->ray->perp_dist = fabs(game->ray->map_hit.y - game->pc->pos.y + ((1 - game->ray->step.y) / 2) / game->ray->dir.y);

        //calcula a altura da linha que representa a parede e o comeco e o fim dela

        game->ray->wall_height_pixel = game->render->win_height / game->ray->perp_dist;
        init_vd2D(&game->ray->wall_line, (game->render->win_height / 2 - game->ray->wall_height_pixel / 2), (game->render->win_height / 2 + game->ray->wall_height_pixel / 2));

        //escolhe textura pelo tipo da parede
        int c;

        c = 0x0000FFFF;
        if(!game->ray->hit_side)
            c = 0x0000FF00;

        t_vd2D wall_b;
        t_vd2D wall_e;

        init_vd2D(&wall_b, pixel, game->ray->wall_line.x);
        init_vd2D(&wall_e, pixel, game->ray->wall_line.y);

        draw_line_with_stroke(game, wall_b, wall_e, c);

        //clear_ray(game->ray);

        pixel++;

    }
}

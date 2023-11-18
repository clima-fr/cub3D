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
    printf("_________SET PERP__________\n");
    if(game->ray->hit_side == V_FACE)
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

    printf("__________RUN DDA__________\n");

    copy_vd2D(&game->ray->dda_line, &game->ray->dist2side);
    print_vd(&game->ray->dda_line, "RAY_dda_line");

    copy_vi2D(&game->ray->map_hit, &game->pc->map_pos);
    printf("[hit_side]\n[int] -> %hd\n\n", game->ray->hit_side);

    while(!hit)
    {
        if(game->ray->dda_line.x < game->ray->dda_line.y)
        {
            game->ray->dda_line.x += game->ray->delta.x;
            game->ray->map_hit.x += game->ray->step.x;
            game->ray->hit_side = V_FACE;
        }
        else
        {
            game->ray->dda_line.y += game->ray->delta.y;
            game->ray->map_hit.y += game->ray->step.y;
            game->ray->hit_side = H_FACE;
        }
        if(game->pc->tmp_map[game->ray->map_hit.x][game->ray->map_hit.y] == '1')
            hit = true;
    }
    print_vd(&game->ray->dda_line, "RAY_dda_line");
    printf("[hit_side]\n[int] -> %hd\n\n", game->ray->hit_side);
}

double calc_d2s(t_general *game, bool x, bool negatv)
{
    if(x && negatv)
        return ((game->pc->pos.x - game->pc->map_pos.x) * game->ray->delta.x);
    else if(x && !negatv)
        return ((game->pc->map_pos.x + 1 - game->pc->pos.x) * game->ray->delta.x);
    else if(!x && negatv)
        return ((game->pc->pos.y - game->pc->map_pos.y) * game->ray->delta.y);
    else if(!x && !negatv)
        return ((game->pc->map_pos.y + 1 - game->pc->pos.y) * game->ray->delta.y);
    return(0);
}

void set_dda(t_general *game)
{
    printf("__________SET DDA__________\n");

    game->ray->delta.x = (game->ray->dir.x == 0) ? 1e30 : fabs(1 / game->ray->dir.x);
    game->ray->delta.y = (game->ray->dir.y == 0) ? 1e30 : fabs(1 / game->ray->dir.y);
    
    print_vd(&game->ray->delta, "RAY_delta");
    
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
    print_vd(&game->ray->dist2side, "RAY_dist2side");
    print_vd2(&game->ray->step, "RAY_step");
}

void set_ray(t_general *game)
{        
    double mult;
    t_vd2D cam_pixel;

    printf("__________SET RAY__________\n");

    mult = (2 * game->ray->pixel/game->render->win_width) - 1;
    printf("[mult]\n[int] -> %f\n\n", mult);
    
    cam_pixel = mult_vd2D(&game->pc->plane, mult);
    print_vd(&cam_pixel, "cam_pixel");

    game->ray->dir = sum_vd2D(&game->pc->dir, &cam_pixel); 
    print_vd(&game->ray->dir, "RAY_dir");

}


//ESTUDAR ESSAS FUNCOES-------------------------------------------------------------------



/*CALCULA ALTURA DA PAREDE DE ACORDO COM A PERP_DIST E 
A POSICAO DE INICIO E FIM DA PAREDE NO CANVAS*/
void	calculate_height_wall(t_general *game)
{
    printf("_______SET HEGHT WALL______\n");
	game->ray->wall_height_pixel = fabs(((double)game->render->win_height / game->ray->perp_dist));
		
	game->ray->line_b = game->render->win_height / 2 - game->ray->wall_height_pixel/2;
	
	game->ray->line_e = game->render->win_height / 2 + game->ray->wall_height_pixel/2;

	printf("[wall_height_pixel]\n[int] -> %f\n\n", game->ray->wall_height_pixel);

    //limita o tamanho da parede a no maximo o tamanho da janela
	if(game->ray->line_b < 0)
		game->ray->line_b = 0;
	if(game->ray->line_e > game->render->win_height)
		game->ray->line_e = game->render->win_height - 1;

    t_vd2D begin;
    set_vd2D(&begin, game->ray->pixel, game->ray->line_b);
    t_vd2D end;
    set_vd2D(&end, game->ray->pixel, game->ray->line_e);
    
    print_ray(game, begin, end, 0x646400);
}

/* void get_tex(t_general *game)
{
    //1 subtracted from it so that texture 0 can be used!
    int texNum = game->pc->tmp_map[game->render->map_hit.x][game->render->map_hit.y] - 1; 

    //calculate value of wallX
    double wallX; //where exactly the wall was hit
    if (game->ray->hit_side == 0) 
        wallX = game->pc->pos.y + game->ray->perp_dist * game->ray->dir.y;
    else
        wallX = game->pc->pos.x + game->ray->perp_dist * game->ray->dir.x;
    wallX -= floor((wallX));

    //x coordinate on the texture
    int texX = int(wallX * double(64));
    if(game->ray->hit_side == 0 && game->ray->dir.x > 0)
        texX = 64 - texX - 1;
    if(game->ray->hit_side== 1 && game->ray->dir.y < 0)
        texX = 64 - texX - 1;

    // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * 64 / game->ray.wall_height_pixel;
    
    // Starting texture coordinate
    double texPos = (game->ray->line_b - h / 2 + lineHeight / 2) * step;
    for(int y = game->ray->line_b; y < game->ray->line_e; y++)
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (64 - 1);
        texPos += step;
        Uint32 color = texture[texNum][64 * texY + texX];

        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(game->ray->hit_side == 1) 
            color = (color >> 1) & 8355711;
        buffer[y][x] = color;
    }
} */

//-----------------------------------------------------------------------------------------------

void  raycaster(t_general *game)
{
    update_img(game);
    game->ray->pixel = 0;
	while (game->ray->pixel < game->render->win_width )
	{
		//ATUALIZAR O MAP_POS JUNTO COM O POS DO PLAYER, OU USAR ELE NO LUGAR DO MAP_HIT E ATUALIZAR AQUI
        print_vd(&game->pc->pos, "PC_pos");
        print_vd(&game->pc->plane, "PC_plane");
        print_vd(&game->pc->dir, "PC_dir");
        print_vd2(&game->pc->map_pos, "PC_mappos");
        printf("-------------------------RAYCASTER BEGIN(%d)------------------------\n", game->ray->pixel);
        printf("|                                                                   |\n");
        printf("|                                                                   |\n");

        set_ray(game);
        set_dda(game);
		dda(game);
        set_perp(game);
        calculate_height_wall(game);
        //get_tex(game);
		game->ray->pixel++;
	}
	mlx_clear_window(game->render->mlx, game->render->win);
    mlx_put_image_to_window(game->render->mlx, game->render->win, game->render->img, 0, 0);
	game->ray->pixel = 0;
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

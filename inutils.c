//imprime um quadrado de 8pxls para representar o player
void print_pc(t_general *game) 
{
	int end_x;
    int end_y;

	end_x = game->pc->pos.x + 4;
	end_y = game->pc->pos.y + 4;
    for (int i = game->pc->pos.x - 4; i < end_x; i++)
	{
        for (int j = game->pc->pos.y - 4; j < end_y; j++) 
            img_pix_put(game->render, i, j, 0x00FF0000);
    }
}


//ALTERAR 
 void print_ray(t_general *game, t_vd2D bg, t_vd2D end)
{
    int dx = abs((int)end.x - (int)bg.x);
    int dy = abs((int)end.y - (int)bg.y);
    int sx = (int)bg.x  < (int)end.x ? 1 : -1;
    int sy = (int)bg.y <  (int)end.y? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) 
    {
        img_pix_put(game->render, (int)bg.x, (int)bg.y, 0x0000FF00);
        if ((int)bg.x == (int)end.x && (int)bg.y == (int)end.y)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            bg.x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            bg.y += sy;
        }
    }
}

//imprime mapa
void print_map(t_general *game) 
{
    int cell_border = 1; // Tamanho da borda da célula

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int x = j * (CELL_SIZE + cell_border);  // Coordenada x da célula
            int y = i * (CELL_SIZE + cell_border);  // Coordenada y da célula

            // Desenha um retângulo preenchido para cada célula '1' no mapa
            for (int dx = 0; dx < CELL_SIZE + cell_border; dx++)
            {
                for (int dy = 0; dy < CELL_SIZE + cell_border; dy++)
                {
                    // Adicionar espaço em branco nas bordas
                    if (dx < cell_border || dy < cell_border || dx >= CELL_SIZE || dy >= CELL_SIZE)
                        img_pix_put(game->render, x + dx, y + dy, 0xFFFFFF);
                    else if (game->pc->tmp_map[i][j] == '1')
                        img_pix_put(game->render, x + dx, y + dy, 0x646464);
                    else
                        img_pix_put(game->render, x + dx, y + dy, 0x000000);
                }
            }
        }
    }
}
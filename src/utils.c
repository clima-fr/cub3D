/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clima-fr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:10:31 by clima-fr          #+#    #+#             */
/*   Updated: 2023/11/29 20:10:32 by clima-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || c == '\n')
		return (1);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	load_tex_addr(t_cub *g, t_tex *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
		&img->line_len, &img->endian);
	if (!img->addr)
		error_xpm(g, "Invalid texture file");
	else
		(void)g;
}

void	load_tex_xpm(t_cub *g, t_tex *img, char *name_xpm, int size)
{
	img->img = mlx_xpm_file_to_image(g->mlx, name_xpm, &size, &size);
	if (!img->img)
		error_xpm(g, "Invalid texture file");
}

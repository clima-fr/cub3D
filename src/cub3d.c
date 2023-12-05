/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:28:59 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 19:29:00 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	verify_name(t_cub *g, char *file, char *type)
{
	int				j;
	unsigned long	i;

	i = 0;
	j = 0;
	if (ft_strlen(file) < 5)
		error(g, "Invalid file extension");
	while (i < ft_strlen(file) - 4)
		i++;
	while (i < ft_strlen(file))
	{
		if (type[j] != file[i])
			error(g, "Invalid file extension");
		i++;
		j++;
	}
}

void	init_game(char *file)
{
	t_cub	g;

	ft_memset(&g, 0, sizeof(t_cub));
	g.ceiling = -1;
	g.floor = -1;
	g.player.coordinate_wall = 0;
	parse(&g, file);
	run_game(&g);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		error(NULL, "Invalid number of arguments");
	verify_name(NULL, av[1], ".cub");
	init_game(av[1]);
}

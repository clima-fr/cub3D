/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clima-fr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:09:45 by clima-fr          #+#    #+#             */
/*   Updated: 2023/11/29 20:09:48 by clima-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_if_all_elements(t_cub *g)
{
	if (!g->n || !g->s || !g->e || !g->w
		|| g->floor == -1 || g->ceiling == -1 || g->check_map != 1)
		error(g, "The input file has the wrong configurations");
}

int	check_ifnsew(t_cub *g, char *line, int i)
{
	int	r;

	r = 1;
	if (line[i] == 'N' && line[i + 1] == 'O')
		check_texture(g, texture_file(line, i + 2), NORTH);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		check_texture(g, texture_file(line, i + 2), SOUTH);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		check_texture(g, texture_file(line, i + 2), EAST);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		check_texture(g, texture_file(line, i + 2), WEST);
	else
		r = 0;
	return (r);
}

int	check_ifcolors(t_cub *g, char *line, int i)
{
	int	r;

	r = 1;
	if (line[i] == 'F')
		check_color(g, get_color(line, i + 1), FLOOR);
	else if (line[i] == 'C')
		check_color(g, get_color(line, i + 1), CEILING);
	else
		r = 0;
	return (r);
}

void	check_elements(t_cub *g, char *line, int i)
{
	while (check_space(line[i]))
		i++;
	if (line[i] && !check_ifnsew(g, line, i) && !check_ifcolors(g, line, i))
	{
		if ((line[i] == '0' || line[i] == '1'))
			g->check_map = 1;
		else
			error(g, "The file has a invalid identifier");
	}
}

void	parse(t_cub *g, char *file)
{
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	i = 0;
	if (fd < 0)
		error(g, "Failed opening the file");
	g->line = get_next_line(fd);
	while (g->line)
	{
		i++;
		check_elements(g, g->line, 0);
		if (g->check_map)
			break ;
		free(g->line);
		g->line = get_next_line(fd);
	}
	if (i <= 0)
		error(g, "File is empty");
	check_if_all_elements(g);
	map_parse(g, fd);
	close (fd);
}

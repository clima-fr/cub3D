/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clima-fr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:08:33 by clima-fr          #+#    #+#             */
/*   Updated: 2023/11/29 20:08:35 by clima-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_character(int c, char *check)
{
	int	i;

	i = 0;
	while (check[i])
	{
		if (check[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	valid_map(t_cub *g, int dir, int l, int c)
{
	if (!g->start)
		error(g, "No player start point");
	while (g->copy_map[l])
	{
		c = 0;
		while (g->copy_map[l][c])
		{
			if (g->copy_map[l][c] != '0' 
			&& !check_character(g->copy_map[l][c], "NSEW"))
			{
				c++;
				continue ;
			}
			dir = 0;
			while (dir < 4)
			{
				if (!check_walls(g, dir, l, c))
					error(g, 
						"The map is not correctly closed/surrounded by walls");
				dir++;
			}
			c++;
		}
		l++;
	}
}

void	map_parse(t_cub *g, int fd)
{
	while (g->line)
	{
		check_line(g, g->line, -1, 0);
		g->temp = ft_strjoin(g->temp, g->line);
		free(g->line);
		g->line = get_next_line(fd);
	}
	g->copy_map = ft_split(g->temp, '\n');
	if (g->temp)
	{
		free(g->temp);
		g->temp = NULL;
	}
	valid_map(g, 0, 0, 0);
	set_first_pos(g, -1, -1);
}

void	check_line(t_cub *g, char *line, int i, int c)
{
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			c++;
		if (!check_character(line[i], " 01NSEW"))
			error(g, "Invalid character in map");
		if (check_character(line[i], "NSEW"))
		{
			if (g->start == 0)
				g->start = line[i];
			else
				error(g, "Multiple player start points");
		}
	}
	if (c == 0)
		error(g, "The map has empty lines");
}

int	check_walls(t_cub *g, int direction, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (direction == 0)
		x = -1;
	if (direction == 1)
		x = 1;
	if (direction == 2)
		y = 1;
	if (direction == 3)
		y = -1;
	while (j >= 0 && i >= 0 && g->copy_map[i]
		&& g->copy_map[i][j] && g->copy_map[i][j] != '1')
	{
		if (g->copy_map[i][j] == ' ')
			return (0);
		i += y;
		j += x;
	}
	return (j >= 0 && i >= 0 && g->copy_map[i]
		&& g->copy_map[i][j] && g->copy_map[i][j] == '1');
}

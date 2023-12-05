/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clima-fr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:55:34 by clima-fr          #+#    #+#             */
/*   Updated: 2023/11/29 19:56:19 by clima-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*texture_file(char *line, int begin)
{
	int	end;

	while (line[begin] && check_space(line[begin]))
		begin++;
	end = begin;
	while (line[end] && !check_space(line[end]))
		end++;
	line[end] = '\0';
	return (line + begin);
}

void	check_texture(t_cub *g, char *file, int face)
{
	int	fd;

	verify_name(g, file, ".xpm");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(g, "Failed opening the texture file");
	close(fd);
	if (face == NORTH && !g->n)
		g->n = ft_strdup(file);
	else if (face == SOUTH && !g->s)
		g->s = ft_strdup(file);
	else if (face == EAST && !g->e)
		g->e = ft_strdup(file);
	else if (face == WEST && !g->w)
		g->w = ft_strdup(file);
	else
		error(g, "Repeated textures");
}

char	*get_color(char *line, int begin)
{
	int	end;

	while (line[begin] && check_space(line[begin]))
		begin++;
	end = begin;
	while (line[end] && line[end] != '\n')
		end++;
	line[end] = '\0';
	return (line + begin);
}

int	is_valid_color_format(char *color)
{
	int	i;

	i = -1;
	while (color[++i])
		if (!ft_isdigit(color[i]) && color[i] != ' ' && color[i] != ',')
			return (0);
	return (count(color, ", ") == 3);
}

void	check_color(t_cub *g, char *rgb, int face)
{
	int	color;
	int	i;

	i = -1;
	if (!is_valid_color_format(rgb))
		error(g, "Invalid color format");
	g->color = ft_separator(rgb, ", ");
	while (g->color[++i])
	{
		if (ft_atoi(g->color[i]) < 0 || ft_atoi(g->color[i]) > 255)
			error(g, "Colors must be between 0 and 255");
	}
	color = (ft_atoi(g->color[0]) << 16) + (ft_atoi(g->color[1]) << 8)
		+ ft_atoi(g->color[2]);
	free_split(g->color);
	g->color = NULL;
	if (face == FLOOR && g->floor == -1)
		g->floor = color;
	else if (face == CEILING && g->ceiling == -1)
		g->ceiling = color;
	else
		error(g, "Repeated colors");
}

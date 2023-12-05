/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:27:58 by ivbatist          #+#    #+#             */
/*   Updated: 2023/11/29 20:28:01 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	error(t_cub *g, char *msg)
{
	free_structure(g);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

void	error_xpm(t_cub *game, char *msg)
{
	if (game->no_tex.img)
		mlx_destroy_image(game->mlx, game->no_tex.img);
	if (game->so_tex.img)
		mlx_destroy_image(game->mlx, game->so_tex.img);
	if (game->ea_tex.img)
		mlx_destroy_image(game->mlx, game->ea_tex.img);
	if (game->we_tex.img)
		mlx_destroy_image(game->mlx, game->we_tex.img);
	if (game->canvas.img)
		mlx_destroy_image(game->mlx, game->canvas.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_structure(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

int	free_mlx(t_cub *game)
{
	mlx_destroy_image(game->mlx, game->canvas.img);
	mlx_destroy_image(game->mlx, game->no_tex.img);
	mlx_destroy_image(game->mlx, game->so_tex.img);
	mlx_destroy_image(game->mlx, game->ea_tex.img);
	mlx_destroy_image(game->mlx, game->we_tex.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_structure(game);
	exit(0);
}

void	free_structure(t_cub *g)
{
	if (!g)
		return ;
	if (g->n)
		free (g->n);
	if (g->s)
		free (g->s);
	if (g->e)
		free (g->e);
	if (g->w)
		free (g->w);
	if (g->line)
		free (g->line);
	if (g->color)
		free_split(g->color);
	if (g->temp)
		free (g->temp);
	if (g->copy_map)
		free_split(g->copy_map);
}

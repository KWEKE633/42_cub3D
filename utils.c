/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:18:21 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 13:40:17 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_errors(t_complete *game)
{
	character_valid(game);
}

int	exit_point(t_complete *game)
{
	int	line;

	line = 0;
	// if (!game)
	// 	exit(1);
	if (game->noth->img)
		mlx_destroy_image(game->mlxpointer, game->noth->img);
	if (game->soth->img)
		mlx_destroy_image(game->mlxpointer, game->soth->img);
	if (game->west->img)
		mlx_destroy_image(game->mlxpointer, game->west->img);
	if (game->east->img)
		mlx_destroy_image(game->mlxpointer, game->east->img);
	if (game->no_tex)
		free(game->no_tex);
	if (game->so_tex)
		free(game->so_tex);
	if (game->ea_tex)
		free(game->ea_tex);
	if (game->we_tex)
		free(game->we_tex);
	if (game->noth)
		free(game->noth);
	if (game->soth)
		free(game->soth);
	if (game->ea_tex)
		free(game->east);
	if (game->we_tex)
		free(game->west);
	if (game->winpointer)
		mlx_destroy_window(game->mlxpointer, game->winpointer);
	if (game->mlxpointer)
		mlx_destroy_display(game->mlxpointer);
	free(game->mlxpointer);
	if (game->widthmap)
		free(game->widthmap);
	while (game->map[line] && line < game->heightmap)
		free(game->map[line++]);
	free(game->map);
	exit(0);
}

int	close_window(t_complete *game)
{
	exit_point(game);
	return (0);
}

int	count_strs(char **strs)
{
	int	count;

	count = 0;
	while (strs && strs[count])
		count++;
	return (count);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:18:21 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 16:57:15 by enkwak           ###   ########.fr       */
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
	if (!game)
		exit(1);
	if (game->mlxpointer)
	{
		if (game->noth && game->noth->img)
			mlx_destroy_image(game->mlxpointer, game->noth->img);
		if (game->soth && game->soth->img)
			mlx_destroy_image(game->mlxpointer, game->soth->img);
		if (game->west && game->west->img)
			mlx_destroy_image(game->mlxpointer, game->west->img);
		if (game->east && game->east->img)
			mlx_destroy_image(game->mlxpointer, game->east->img);
		if (game->winpointer)
			mlx_destroy_window(game->mlxpointer, game->winpointer);
		mlx_destroy_display(game->mlxpointer);
		free(game->mlxpointer);
	}
	free(game->no_tex);
	free(game->so_tex);
	free(game->ea_tex);
	free(game->we_tex);
	free(game->noth);
	free(game->soth);
	free(game->west);
	free(game->east);
	free(game->widthmap);
	if (game->map)
	{
		while (game->map[line])
			free(game->map[line++]);
		free(game->map);
	}
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
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

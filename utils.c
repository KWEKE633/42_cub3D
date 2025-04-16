/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:18:21 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/17 06:04:23 by enkwak           ###   ########.fr       */
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
	// if (game->noth)
	// 	mlx_destroy_image(game->mlxpointer, game->noth);
	// if (game->soth)
	// 	mlx_destroy_image(game->mlxpointer, game->soth);
	// if (game->west)
	// 	mlx_destroy_image(game->mlxpointer, game->west);
	// if (game->east)
	// 	mlx_destroy_image(game->mlxpointer, game->east);
	if (game->winpointer)
		mlx_destroy_window(game->mlxpointer, game->winpointer);
	if (game->mlxpointer)
		mlx_destroy_display(game->mlxpointer);
	free(game->mlxpointer);
	while (line < game->heightmap)
		free(game->map[line++]);
	while (line < game->heightmap)
		free(game->widthmap);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:18:21 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/14 16:06:15 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_errors(t_complete *game)
{
	if_walls(game);
	character_valid(game);
}

int	exit_point(t_complete *game)
{
	int	line;

	line = 0;
	// if (game->player)
	// 	mlx_destroy_image(game->mlxpointer, game->player);
	// if (game->floor)
	// 	mlx_destroy_image(game->mlxpointer, game->floor);
	if (game->barrier)
		mlx_destroy_image(game->mlxpointer, game->barrier);
	if (game->winpointer)
		mlx_destroy_window(game->mlxpointer, game->winpointer);
	if (game->mlxpointer)
		mlx_destroy_display(game->mlxpointer);
	free(game->mlxpointer);
	while (line < game->heightmap)
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
	int	count = 0;

	while (strs && strs[count])
		count++;
	return (count);
}

void	free_strs(char **strs)
{
	int	i = 0;

	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:01 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/14 17:19:16 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	horizontalwall(t_complete *game)
{
	int	i;
	int	j;

	i = game->widthmap;
	j = 0;
	while (j < i)
	{
		if (game->map[0][i] == '1' && game->map[game->heightmap - 1][i] == '1')
			return (0);
		j++;
	}
	return (1);
}

static int	verticalwall(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	width = game->widthmap;
	while (height < game->heightmap)
	{
		if (!(game->map[height][0] == '1'
			&& game->map[height][width - 1] == '1'))
			return (0);
		height++;
	}
	return (1);
}

void	if_walls(t_complete *game)
{
	int	verticalwalls;
	int	horizontalwalls;

	verticalwalls = verticalwall(game);
	horizontalwalls = horizontalwall(game);
	if (!verticalwalls || !horizontalwalls)
	{
		ft_printf("\nError\nThis map is missing the walls\n");
		exit_point(game);
	}
}

static void	count_checker(t_complete *game, int height, int width)
{
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'N' &&
		game->map[height][width] != 'S' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'W' &&
		game->map[height][width] != '\n')
	{
		ft_printf("Error\nHere!%c\n", game->map[height][width]);
		exit_point(game);
	}
	if (game->map[height][width] == 'N')
		game->playercount++;
	if (game->map[height][width] == 'S')
		game->playercount++;
	if (game->map[height][width] == 'E')
		game->playercount++;
	if (game->map[height][width] == 'W')
		game->playercount++;
}

void	character_valid(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->heightmap - 1)
	{
		width = 0;
		while (width <= game->widthmap)
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
	}
	if (!(game->playercount == 1))
	{
		ft_printf("\nError\nplayer is wrong!\n");
		exit_point(game);
	}
}

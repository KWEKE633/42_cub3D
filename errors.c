/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:01 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 07:51:06 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	map_all_wall(char **map, int height)
{
	int x;
	int y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	get_player_pos(t_complete *game, int *px, int *py)
{
	for (int y = 0; y < game->heightmap; y++)
	{
		for (int x = 0; game->map[y][x]; x++)
		{
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				*px = x;
				*py = y;
				return ;
			}
		}
	}
}

static int	flood_fill(char **map, int y, int x, int height, int *width)
{
	if (y < 0 || y >= height || x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	map[y][x] = 'X';
	if (!flood_fill(map, y + 1, x, height, &width[y + 1]))
		return (0);
	if (!flood_fill(map, y - 1, x, height, &width[y - 1]))
		return (0);
	if (!flood_fill(map, y, x + 1, height, &width[y]))
		return (0);
	if (!flood_fill(map, y, x - 1, height, &width[y]))
		return (0);
	return (1);
}

static void	count_checker(t_complete *game, int height, int width)
{
	if (game->map[height][width] != ' ' && game->map[height][width] != '1'
		&& game->map[height][width] != '0' && game->map[height][width] != 'N'
		&& game->map[height][width] != 'S' && game->map[height][width] != 'E'
		&& game->map[height][width] != 'W' && game->map[height][width] != '\n')
	{
		ft_printf("Error\nHere!%c\n", game->map[height][width]);
		exit_point(game);
	}
	if (ft_strchr("NSEW", game->map[height][width]))
	{
		game->player.x = width + 0.5;
		game->player.y = height + 0.5;
		set_player_dir(&game->player, game->map[height][width]);
		game->playercount++;
	}
}

char	**deep_copy_map(char **src, int height)
{
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	for (int i = 0; i < height; i++)
	{	
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
		{
			free_strs(copy);
			return (NULL);
		}
	}
	copy[height] = NULL;
	return (copy);
}

void	character_valid(t_complete *game)
{
	int		height;
	int		width;
	int		i;
	int		player_x;
	int		player_y;
	char	**map_copy;

	i = 0;
	height = 0;
	while (height < game->heightmap - 1)
	{
		width = 0;
		while (width <= game->widthmap[i])
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
		i++;
	}
	if (!(game->playercount == 1))
	{
		ft_printf("\nError\nplayer is wrong!\n");
		exit_point(game);
	}
	get_player_pos(game, &player_x, &player_y);
	map_copy = deep_copy_map(game->map, game->heightmap);
	if (!map_copy || !flood_fill(map_copy, player_y, player_x, game->heightmap,
			game->widthmap) || !map_all_wall(map_copy, game->heightmap))
	{
		ft_printf("\nError\nMap is not closed properly!\n");
		free_strs(map_copy);
		exit_point(game);
	}
	free_strs(map_copy);
}

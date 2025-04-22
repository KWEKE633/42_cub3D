/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:01 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/22 13:11:30 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_player_pos(t_complete *game, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->heightmap)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

static int	flood_fill(char **map, int y, int x, int height)
{
	if (!map[y][x] || y < 0 || y >= height || x < 0
		|| x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	map[y][x] = 'X';
	if (!flood_fill(map, y + 1, x, height))
		return (0);
	if (!flood_fill(map, y - 1, x, height))
		return (0);
	if (!flood_fill(map, y, x + 1, height))
		return (0);
	if (!flood_fill(map, y, x - 1, height))
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
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
		{
			free_strs(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

void	character_valid(t_complete *game)
{
	t_char	c;

	ft_memset(&c, 0, sizeof(t_char));
	while (c.height++ < game->heightmap - 1)
	{
		c.width = 0;
		while (c.width++ <= game->widthmap[c.i])
			count_checker(game, c.height - 1, c.width - 1);
		c.i++;
	}
	if (!(game->playercount == 1))
	{
		ft_printf("\nError\nplayer is wrong!\n");
		exit_point(game);
	}
	get_player_pos(game, &c.player_x, &c.player_y);
	c.map_copy = deep_copy_map(game->map, game->heightmap);
	if (!c.map_copy || !flood_fill(c.map_copy, c.player_y, c.player_x,
			game->heightmap) || !map_all_wall(c.map_copy, game->heightmap))
	{
		ft_printf("\nError\nMap is not closed properly!\n");
		free_strs(c.map_copy);
		exit_point(game);
	}
	free_strs(c.map_copy);
}

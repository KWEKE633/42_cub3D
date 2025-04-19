/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:21:14 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 16:50:14 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	width_of_map(char *string)
{
	int	width;

	width = 0;
	while (string[width] != '\0')
		width++;
	if (string[width - 1] == '\n')
		width--;
	return (width);
}

static int	add_line(t_complete *game, char *line)
{
	char	**temporary;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->heightmap++;
	temporary = (char **)malloc(sizeof(char *) * (game->heightmap + 1));
	if (!temporary)
	{
		ft_printf("Error\nMemory allocation failed\n");
		return (0);
	}
	temporary[game->heightmap] = NULL;
	while (i < game->heightmap - 1)
	{
		temporary[i] = game->map[i];
		i++;
	}
	temporary[i] = line;
	if (game->map)
		free(game->map);
	game->map = temporary;
	return (1);
}

int	map_reading(t_complete *game, char *line)
{
	int	i;
	int j;

	j = 1;
	while (1)
	{
		if (!add_line(game, line))
		{
			free(line);
			break ;
		}
		line = get_next_line(game->fd);
		if (!line)
			break ;
		j++;
	}
	close (game->fd);
	i = 0;
	game->widthmap =  (int *)malloc(sizeof(int) * (j + 1));
	while (game->map[i])
	{
		game->widthmap[i] = width_of_map(game->map[i]);
		i++;
	}
	if (!game->widthmap)
		free(game->widthmap);
	game->widthmap[i] = 0;
	return (1);
}

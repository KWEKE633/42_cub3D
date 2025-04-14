/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:21:14 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/14 19:07:16 by enkwak           ###   ########.fr       */
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

// int	map_reading(t_complete *game, char *argv)
// {
// 	char	*read_map;

// 	game->fd = open(argv, O_RDONLY);
// 	if (game->fd < 0)
// 		return (0);
// 	while (1)
// 	{
// 		read_map = get_next_line(game->fd);
// 		if (!read_map)
// 			break ;
// 		if (!add_line(game, read_map))
// 		{
// 			free(read_map);
// 			break ;
// 		}
// 	}
// 	close (game->fd);
// 	game->widthmap = width_of_map(game->map[0]);
// 	return (1);
// }

int	map_reading(t_complete *game, char *line)
{
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
	}
	close (game->fd);
	game->widthmap = width_of_map(game->map[0]);
	return (1);
}

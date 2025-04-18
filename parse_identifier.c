/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:55 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 13:15:31 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_rgb(char *str)
{
	char	**split;
	int		color;

	int r, g, b;
	split = ft_split(str, ',');
	if (!split || count_strs(split) != 3)
		return (free_strs(split), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_strs(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

int	parse_identifier(t_complete *game, char *line)
{
	char	**tokens;
	int		color;

	tokens = ft_split(line, ' ');
	if (!tokens || count_strs(tokens) < 2 || !tokens[1])
		return (free_strs(tokens), ft_printf("Error\nIdentifier 行が不正: %s\n",
				line), 1);
	if (ft_strcmp(tokens[0], "NO") == 0 || ft_strcmp(tokens[0], "SO") == 0
		|| ft_strcmp(tokens[0], "WE") == 0 || ft_strcmp(tokens[0], "EA") == 0)
		return (free_strs(tokens), 0);
	else if (ft_strcmp(tokens[0], "F") == 0)
	{
		if (!tokens[1])
			return (free_strs(tokens), ft_printf("Error\nFの色指定がありません\n"), 1);
		color = parse_rgb(tokens[1]);
		if (color == -1)
			return (free_strs(tokens), ft_printf("Error\nFの色指定が不正です\n"), 1);
		game->floor_color = color;
	}
	else if (ft_strcmp(tokens[0], "C") == 0)
	{
		if (!tokens[1])
			return (free_strs(tokens), ft_printf("Error\nFの色指定がありません\n"), 1);
		color = parse_rgb(tokens[1]);
		if (color == -1)
			return (free_strs(tokens), ft_printf("Error\nCの色指定が不正です\n"), 1);
		game->ceiling_color = color;
	}
	else
		return (free_strs(tokens), ft_printf("Error\n未知の識別子\n"), 1);
	free_strs(tokens);
	return (0);
}

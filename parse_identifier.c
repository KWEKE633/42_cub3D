/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:55 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 14:43:34 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_atoi_cub(char *str)
{
	unsigned int		i;
	unsigned long long	number;

	i = 0;
	number = 0;
	if ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		return(-1);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] && str[i] != '\n')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		number = (str[i] - '0') + (number * 10);
		if (number < 0 || number > 255)
			return (-1);
		i++;
	}
	if (str[i] != '\0' && str[i] != '\n')
		return (-1);
	return (number);
}

static int	parse_rgb(char *str)
{
	char	**split;
	int		color;

	int r, g, b;
	split = ft_split(str, ',');
	if (!split || count_strs(split) != 3)
		return (free_strs(split), -1);
	r = ft_atoi_cub(split[0]);
	g = ft_atoi_cub(split[1]);
	b = ft_atoi_cub(split[2]);
	free_strs(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

static int	judge_parse_identifier(char *line)
{
	static int	direction[4];
	static int	color[2];

	if (ft_strcmp(line, "NO") == 0)
		direction[0]++;
	else if (ft_strcmp(line, "SO") == 0)
		direction[1]++;
	else if (ft_strcmp(line, "WE") == 0)
		direction[2]++;
	else if (ft_strcmp(line, "EA") == 0)
		direction[3]++;
	else if (ft_strcmp(line, "F") == 0)
		color[0]++;
	else if (ft_strcmp(line, "C") == 0)
		color[1]++;
	else
		return (ft_printf("Error\n未知の識別子\n"), 1);
	if (direction[0] > 1 || direction[1] > 1 || direction[2] > 1
		|| direction[3] > 1 || color[0] > 1 || color[1] > 1)
		return (1);
	return (0);
}

int	parse_identifier(t_complete *game, char *line)
{
	char	**tokens;
	int		color;

	tokens = ft_split(line, ' ');
	if (!tokens || judge_parse_identifier(tokens[0]) || count_strs(tokens) < 2
		|| !tokens[1])
		return (free_strs(tokens), ft_printf("Error\nIdentifier 行が不正: %s\n",
				line), 1);
	if (ft_strcmp(tokens[0], "F") == 0)
	{
		color = parse_rgb(tokens[1]);
		if (color == -1)
			return (free_strs(tokens), ft_printf("Error\nFの色指定が不正です\n"), 1);
		game->floor_color = color;
	}
	else if (ft_strcmp(tokens[0], "C") == 0)
	{
		color = parse_rgb(tokens[1]);
		if (color == -1)
			return (free_strs(tokens), ft_printf("Error\nCの色指定が不正です\n"), 1);
		game->ceiling_color = color;
	}
	free_strs(tokens);
	return (0);
}

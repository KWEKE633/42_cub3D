/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:38:13 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 16:58:24 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

static void	set_texture(char **target, char *line, t_complete *conf)
{
	while (*line && *line == ' ')
		line++;
	*target = ft_strdup(line);
	if (!*target || !target)
	{
		free_strs(target);
		exit_point(conf);
	}
}

static void	handle_identifier(t_complete *conf, char *line)
{
	static int	vec[6];

	if (ft_strncmp(line, "NO ", 3) == 0 && !vec[0])
	{
		set_texture(&conf->no_tex, line + 3, conf);
		vec[0]++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !vec[1])
	{
		set_texture(&conf->so_tex, line + 3, conf);
		vec[1]++;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 && !vec[2])
	{
		set_texture(&conf->we_tex, line + 3, conf);
		vec[2]++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !vec[3])
	{
		set_texture(&conf->ea_tex, line + 3, conf);
		vec[3]++;
	}
	else if (ft_strncmp(line, "F ", 2) == 0 && !vec[4])
	{
		set_color(&conf->floor, line + 2);
		vec[4]++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !vec[5])
	{
		set_color(&conf->ceiling, line + 2);
		vec[5]++;
	}
}

int	parse_cubfile(t_complete *game, char *filename)
{
	char	*line;
	int		count;

	count = 0;
	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		return (perror("open"), 1);
	line = get_next_line(game->fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(game->fd);
			continue ;
		}
		if (ft_strchr("NSWEFC", line[0]))
		{
			handle_identifier(game, line);
			if (parse_identifier(game, line))
				return (free(line), 1);
			count++;
		}
		else
			break ;
		free(line);
		line = get_next_line(game->fd);
	}
	if (!line)
		return (close(game->fd), ft_printf("Error\nNo such map\n"), 1);
	if (count != 6)
		return (free(line), close(game->fd),
			ft_printf("Error\n invalid element\n"));
	if (!map_reading(game, line))
		return (free(line), close(game->fd), 1);
	close(game->fd);
	return (0);
}

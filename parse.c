/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:38:13 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/22 13:01:48 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_texture(char **target, char *line, t_complete *conf)
{
	char	*end;

	while (*line && *line == ' ')
		line++;
	end = line + ft_strlen(line) - 1;
	while (end > line && (*end == '\n'))
	{
		*end = '\0';
		end--;
	}
	*target = ft_strdup(line);
	if (!*target || !target)
	{
		free_strs(target);
		exit_point(conf);
	}
}

static void	handle_identifier(t_complete *conf, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_texture(&conf->no_tex, line + 3, conf);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_texture(&conf->so_tex, line + 3, conf);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_texture(&conf->we_tex, line + 3, conf);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_texture(&conf->ea_tex, line + 3, conf);
	else if (ft_strncmp(line, "F ", 2) == 0)
		set_color(&conf->floor, line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		set_color(&conf->ceiling, line + 2);
}

int	read_identifiers(t_complete *game, char **line, int *count)
{
	while (*line)
	{
		if (is_empty_line(*line))
		{
			free(*line);
			*line = get_next_line(game->fd);
			continue ;
		}
		if (ft_strchr("NSWEFC", (*line)[0]))
		{
			handle_identifier(game, *line);
			if (parse_identifier(game, *line))
				return (free(*line), 1);
			(*count)++;
		}
		else
			break ;
		free(*line);
		*line = get_next_line(game->fd);
	}
	return (0);
}

int	read_map_section(t_complete *game, char *line)
{
	if (!line)
		return (ft_printf("Error\nNo such map\n"), 1);
	if (!map_reading(game, line))
		return (1);
	return (0);
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
	if (read_identifiers(game, &line, &count))
		return (close(game->fd), 1);
	if (count != 6)
		return (free(line), close(game->fd),
			ft_printf("Error\ninvalid element\n"), 1);
	if (read_map_section(game, line))
		return (close(game->fd), 1);
	close(game->fd);
	return (0);
}

// int	parse_cubfile(t_complete *game, char *filename)
// {
// 	char	*line;
// 	int		count;

// 	count = 0;
// 	game->fd = open(filename, O_RDONLY);
// 	if (game->fd < 0)
// 		return (perror("open"), 1);
// 	line = get_next_line(game->fd);
// 	while (line)
// 	{
// 		if (is_empty_line(line))
// 		{
// 			free(line);
// 			line = get_next_line(game->fd);
// 			continue ;
// 		}
// 		if (ft_strchr("NSWEFC", line[0]))
// 		{
// 			handle_identifier(game, line);
// 			if (parse_identifier(game, line))
// 				return (free(line), 1);
// 			count++;
// 		}
// 		else
// 			break ;
// 		free(line);
// 		line = get_next_line(game->fd);
// 	}
// 	if (!line)
// 		return (close(game->fd), ft_printf("Error\nNo such map\n"), 1);
// 	if (count != 6)
// 		return (free(line), close(game->fd),
// 			ft_printf("Error\n invalid element\n"));
// 	if (!map_reading(game, line))
// 		return (free(line), close(game->fd), 1);
// 	close(game->fd);
// 	return (0);
// }

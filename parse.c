/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:38:13 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/14 19:07:32 by enkwak           ###   ########.fr       */
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

static void	set_texture(char **target, char *line)
{
	while (*line && *line == ' ')
		line++;
	*target = strdup(line);
}

static void	handle_identifier(t_complete *conf, char *line)
{
	if (strncmp(line, "NO ", 3) == 0)
		set_texture(&conf->no_tex, line + 3);
	else if (strncmp(line, "SO ", 3) == 0)
		set_texture(&conf->so_tex, line + 3);
	else if (strncmp(line, "WE ", 3) == 0)
		set_texture(&conf->we_tex, line + 3);
	else if (strncmp(line, "EA ", 3) == 0)
		set_texture(&conf->ea_tex, line + 3);
	else if (strncmp(line, "F ", 2) == 0)
		set_color(&conf->floor, line + 2);
	else if (strncmp(line, "C ", 2) == 0)
		set_color(&conf->ceiling, line + 2);
}

// int	parse_cubfile(t_complete *game, char *filename)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (perror("open"), 1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (is_empty_line(line))
// 		{
// 			free(line);
// 			line = get_next_line(fd);
// 			continue ;
// 		}
// 		if (is_map_line(line))
// 			break ;
// 		if (parse_identifier(game, line))
// 			return (1);
// 		if (strchr("NSWEFC", line[0]))
// 			handle_identifier(game, line);
// 		else
// 			break ;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	if (!line)
// 		return (ft_printf("Error\nNo such map\n"), 1);
// 	if (!map_reading(game, filename))
// 		return (1);
// 	close(fd);
// 	return (0);
// }

int	parse_cubfile(t_complete *game, char *filename)
{
	// int		fd;
	char	*line;

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
		// if (is_map_line(line))
		// 	break ;
		// if (parse_identifier(game, line))
		// 	return (1);
		if (strchr("NSWEFC", line[0]))
		{
			handle_identifier(game, line);
			if (parse_identifier(game, line))
				return (1);
		}
		else
			break ;
		free(line);
		line = get_next_line(game->fd);
	}
	if (!line)
		return (ft_printf("Error\nNo such map\n"), 1);
	// if (!map_reading(game, filename))
	// 	return (1);
	if (!map_reading(game, line))
		return (1);
	close(game->fd);
	return (0);
}

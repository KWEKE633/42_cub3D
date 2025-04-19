/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:36:08 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 16:32:30 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_null(char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*join_line(int nl_position, char **buffer)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	if (nl_position <= 0)
	{
		if (**buffer == '\0')
		{
			free_null(buffer);
			return (NULL);
		}
		res = *buffer;
		*buffer = NULL;
		return (res);
	}
	tmp = ft_substr_gnl(*buffer, nl_position, BUFFER_SIZE);
	if (tmp == NULL)
	{
		free_null(buffer);
		return (NULL);
	}
	res = *buffer;
	res[nl_position] = '\0';
	*buffer = tmp;
	return (res);
}

char	*read_line(int fd, char **buffer, char *read_return)
{
	ssize_t	bytes_read;
	char	*tmp;
	char	*nl;

	nl = ft_strchr_gnl(*buffer, '\n');
	tmp = NULL;
	bytes_read = 0;
	while (nl == NULL)
	{
		bytes_read = read(fd, read_return, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (join_line(bytes_read, buffer));
		read_return[bytes_read] = '\0';
		tmp = ft_strjoin_gnl(*buffer, read_return);
		if (tmp == NULL)
		{
			free_null(buffer);
			return (NULL);
		}
		free_null(buffer);
		*buffer = tmp;
		nl = ft_strchr_gnl(*buffer, '\n');
	}
	return (join_line(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD + 1];
	char		*read_return;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	read_return = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_return == NULL)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_strdup_gnl("");
		if (buffer[fd] == NULL)
		{
			free_null(&read_return);
			return (NULL);
		}
	}
	res = read_line(fd, &buffer[fd], read_return);
	free_null(&read_return);
	return (res);
}

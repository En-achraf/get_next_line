/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:19:44 by acennadi          #+#    #+#             */
/*   Updated: 2025/01/24 11:33:28 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*rm_line(char *saved)
{
	int		i;
	char	*new_buff;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	i++;
	new_buff = ft_strdup(&saved[i]);
	free(saved);
	return (new_buff);
}

char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	while (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_saved(char *saved, int fd)
{
	char	*buffer;
	ssize_t	count;

	buffer = malloc(BUFFER_SIZE + (size_t)1);
	count = 1;
	if (!buffer)
		return (NULL);
	while (count > 0 && !ft_findchr(buffer, '\n'))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[count] = '\0';
		saved = ft_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	saved[fd] = get_saved(saved[fd], fd);
	if (!saved[fd])
		return (NULL);
	line = get_line(saved[fd]);
	saved[fd] = rm_line(saved[fd]);
	return (line);
}

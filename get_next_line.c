/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:04:18 by acennadi          #+#    #+#             */
/*   Updated: 2025/01/12 17:02:07 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find_newline(char *str, int *sum)
{
	while (*str && *str != '\n')
	{
		str++;
	}
	if (*str == '\n')
		*sum = 1;
	else
		*sum = 0;
	return (str);
}

char	*ft_saved(int fd, char *buffer)
{
	int	count;

	count = read(fd, buffer, BUFFER_SIZE);
	if (count <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[count] = '\0';
	return (buffer);
}

char	*process_line(char *saved, char *tmp, int sum)
{
	int		len_line;
	char	*line;

	len_line = tmp - saved + sum;
	line = malloc(len_line + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, saved, len_line + 1);
	return (line);
}

char	*handle_remaining(char *tmp, char *buffer, char **saved)
{
	if (*tmp == '\n')
		tmp++;
	if (*tmp)
	{
		*saved = ft_strdup(tmp);
		free(buffer);
	}
	else
	{
		free(*saved);
		*saved = NULL;
	}
	return (*saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	int			sum;
	char		*tmp;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!saved)
	{
		buffer = malloc(BUFFER_SIZE + (size_t)1);
		if (!buffer)
			return (NULL);
		saved = ft_saved(fd, buffer);
	}
	if (!saved)
		return (NULL);
	tmp = ft_find_newline(saved, &sum);
	line = process_line(saved, tmp, sum);
	buffer = saved;
	handle_remaining(tmp, buffer, &saved);
	return (line);
}

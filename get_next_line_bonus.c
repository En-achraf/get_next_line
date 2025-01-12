/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:19:44 by acennadi          #+#    #+#             */
/*   Updated: 2025/01/12 17:02:38 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_find_newline(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '\n')
		str++;
	return (str);
}

char	*ft_saved_line(char *str, int fd)
{
	int	count;

	count = read(fd, str, BUFFER_SIZE);
	if (count <= 0)
	{
		free(str);
		return (NULL);
	}
	str[count] = '\0';
	return (str);
}

char	*process_line(char *saved, char *tmp)
{
	int		len_line;
	int		sum;
	char	*line;

	if (!saved || !tmp)
		return (NULL);
	sum = 0;
	if (*tmp == '\n')
		sum = 1;
	len_line = tmp - saved + sum;
	line = malloc(len_line + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, saved, len_line + 1);
	return (line);
}

void	handle_remaining(char *tmp, char **saved)
{
	char	*new_saved;

	if (*tmp == '\n')
		tmp++;
	if (*tmp)
	{
		new_saved = ft_strdup(tmp);
		free(*saved);
		*saved = new_saved;
	}
	else
	{
		free(*saved);
		*saved = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*saved[1024];
	char		*buffer;
	char		*tmp;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	if (!saved[fd])
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		saved[fd] = ft_saved_line(buffer, fd);
		if (!saved[fd])
			return (NULL);
	}
	tmp = ft_find_newline(saved[fd]);
	if (!tmp)
		return (NULL);
	line = process_line(saved[fd], tmp);
	if (!line)
		return (NULL);
	handle_remaining(tmp, &saved[fd]);
	return (line);
}

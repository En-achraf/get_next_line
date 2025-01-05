#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *saved; 
    char *buffer;
    char *line;
    char *temp;
    int count;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (!saved)
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer)
            return (NULL);
        count = read(fd, buffer, BUFFER_SIZE);
        if (count <= 0)
        {
            free(buffer);
            return (NULL);
        }
        buffer[count] = '\0';
        saved = buffer;
    }

    temp = saved;
    while (*temp && *temp != '\n')
        temp++;
    int sum;

    if(*temp == '\n')
        sum = 1;
    else
        sum = 0;

    int line_len = temp - saved + sum;
    line = malloc(line_len + 1);
    if (!line)
        return (NULL);

    int i = 0;
    while (i < line_len)
    {
        line[i] = saved[i];
        i++;
    }
    line[i] = '\0';

    if (*temp == '\n')
        temp++;
    
    buffer = saved;
    if (*temp)
    {
        saved = ft_strdup(temp);
        free(buffer);
    }
    else
    {
        free(saved);
        saved = NULL;
    }
    
    return (line);
}

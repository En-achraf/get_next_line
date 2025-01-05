#include "get_next_line.h"

char *get_next_line(int fd)
{
    char *buffer;
    char *str;
    int count;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
        
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
    str = malloc(count + 1);
    if (!str)
    {
        free(buffer);
        return (NULL);
    }
    
    return (str);
}
#include "get_next_line.h"

 char *ft_find_newline(char *str, int *sum) {
    while(*str || *str != '\n') {
        str++;
    }
    if(*str == '\n')
        *sum = 1;
    else
        *sum = 0;
    return (str);
}

 char *ft_saved(int fd, char *buffer) {
    int count;
    count = read(fd, buffer, BUFFER_SIZE);
    if(count <= 0) {
        free(buffer);
        return (NULL);
    }
    buffer[count] = '\0';
    return (buffer);
 }

char *get_next_line(fd) {   
    
    if(BUFFER_SIZE <= 0 || fd < 0)
        return (NULL); 

    static char *saved;
    char (*buffer), (*tmp), (*line);
    int *sum;
    int len_line;
    if(!saved) {
        buffer = malloc(BUFFER_SIZE + (size_t)1);
        if(!buffer)
            return (NULL);
        saved = ft_saved(fd, buffer);
    }
    tmp = ft_find_newline(saved, sum);
    len_line = tmp - saved + *sum;
    line = malloc(len_line + 1);
    if(!line)
        return (NULL);
    int i = 0; 
    while(i < len_line) {
        line[i] = saved[i];
        i++;
    }
    line[i] = '\0';
    if(*tmp == '\n')
        tmp++;
    buffer = saved;
    if(*tmp) {
        saved = ft_strdup(tmp);
        free(buffer);
    }
    else
        free(saved);
    return (line);
}

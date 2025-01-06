#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    // Test with regular file
    printf("\n=== Testing with regular file ===\n");
    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file\n");
        return (1);
    }
    
    // Read and print line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
    close(fd);

    // Test with invalid fd
    printf("\n=== Testing with invalid fd ===\n");
    line = get_next_line(-1);
    if (!line)
        printf("Successfully returned NULL for invalid fd\n");

    // Test with stdin
    printf("\n=== Testing with stdin (type something) ===\n");
    line = get_next_line(0);  // 0 is stdin
    if (line)
    {
        printf("Read from stdin: %s", line);
        free(line);
    }

    return (0);
}
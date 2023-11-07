#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void main(int argc, char *argv[])
{
    char *name, line, size;
    int i = 0, fd, n;
    fd = open(argv[1], O_RDONLY);
    while (read(fd, &line, 1) > 0)
    {
        if (line == '\n')
        {
            i++;
        }
        if (i % 2 == 0)
        {
            write(STDOUT_FILENO, &line, 1);
        }
    }
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void main(int argc, char *argv[])
{
    int fd, i, n;
    char cat;
    for (i = 1; i < argc; i++)
    {
        if ((fd = open(argv[i], O_RDONLY)) < 0)
        {
            printf("\nNo se ha podido leer %s\n", argv[i]);
        }
        else
        {
            while ((n = read(fd, &cat, 1)) > 0)
            {
                write(1, &cat, 1);
            }
        }
    }
}

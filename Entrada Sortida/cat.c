#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 10000
void main(int argc, char *argv)
{
    int fd, i, n;
    char car, tmp[100];
    for (i = 1; i < argc; i++)
    {
        if ((fd = open(argv[i], O_RDONLY)) < 0)
        {
            sprintf(tmp, "Error open %s\n", argv[i]);
            write(2, tmp, strlen(tmp));
        }
        while ((n = read(fd, &car, 1)) > 0)
            write(1, &car, 1);
    }
}
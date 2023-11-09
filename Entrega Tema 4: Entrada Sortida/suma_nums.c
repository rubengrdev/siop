#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define F 2
#define dignits 5
void main(int argc, char *argv[])
{
    int num, n, i, fd;
    if (argc != 2)
        perror("args");
    if (fd = open(argv[1], O_RDONLY < 0))
        ;
    i = 0;
    while (n = read(0, F, sizeof(char) * dignits) > 0)
    {
        num = atoi(F);
        if (n = write(fd, &num, sizeof(int)) < 0)
            perror("write");
    }
}
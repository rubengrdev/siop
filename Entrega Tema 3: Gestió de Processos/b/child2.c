#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main(int argc, char *argv[])
{
    execlp(argv[0], argv[0], NULL);
    exit(0);
}
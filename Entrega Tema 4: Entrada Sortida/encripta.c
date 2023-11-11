#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void trataExitCode(int);

void main(int argc, char *argv[])
{
    int i, n, exitcode, pid;
    pid_t mypod;
    char c, cc, buff[30];
    int key = getpid()%10;



}

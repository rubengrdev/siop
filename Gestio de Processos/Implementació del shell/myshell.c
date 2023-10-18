#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
//@pre entrada tipus myshell cmd1 cmd2 cmd3
void main(int argc, char *argv[])
{

    int pid, i;
    if (argc != 4)
    {
        exit(-1);
    }

    for (i = 0; i < argc - 1; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            execlp(argv[i+1], argv[i+2], NULL);
            close(0);
        }else{
            wait(NULL);
        }
    }
}
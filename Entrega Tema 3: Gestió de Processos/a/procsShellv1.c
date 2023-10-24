#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#define MAX 50
//@pre entrada tipus myshell cmd1 cmd2 cmd3
void main()
{

    int num, pid, stat, exitstat, returnstat;
    char cmd[MAX];
    printf("Indica la teva comanda (sense arguments): ");
    num = scanf("%s", cmd);
    // inserta comanda i la guarda a la variable cmd

    pid = fork();
    if (pid == 0)
    {
        execlp("./child", cmd, NULL);
    }

    while ((wait(&stat) > 0))
    {

        if (WIFEXITED(stat))
        {
            exit(0);
        }

        if (WIFSIGNALED(stat))
        {
            psignal(WTERMSIG(stat), "Forzando cierre del proceso");
        }
    }
}
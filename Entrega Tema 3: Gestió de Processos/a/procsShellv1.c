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
            exitstat = WEXITSTATUS(stat);
            // en el caso de que en WEXITSTATUS(stat) yo reciba un 0, todo ha ido bien, si stat recibe un 255 significará que el exit de replicant ha sido -1
            if (exitstat == 255)
            {
                exitstat = -1;
            }
        }

        if (WIFSIGNALED(stat))
        {
            psignal(WTERMSIG(stat), "Forzando cierre del proceso");
        }
    }
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#define MAX 50
void main(int argc, char *argv[])
{
    int num, pid, exitstat, stat;
    char cmd[MAX];
    ;

    while (1)
    {
        num = scanf("%s", cmd);
        // inserta comanda i la guarda a la variable cmd

        if (strcmp(cmd, "exit") == 0)
        {
            exit(0);
        }
        pid = fork();
        if (pid == 0)
        {
            printf("\nExecutant %s amb PID = %d\n", argv[0], getpid());
            execlp(cmd, cmd, NULL);
        }
        else
        {
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
                    printf("El proceso %d termina con exit code %d\n", getpid(), exitstat);
                }
                if (WIFSIGNALED(stat))
                {
                    psignal(WTERMSIG(stat), "Forzando cierre del proceso");
                }

            }

        }
    }
}
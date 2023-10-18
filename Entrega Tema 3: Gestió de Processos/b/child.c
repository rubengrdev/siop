#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

void main(int argc, char *argv[])
{
    int pid_child1, exitstat, stat;

    printf("\nExecutant %s amb PID = %d\n", argv[0], getpid());
    // executar al background, si argv[2] = 1, true, si argv[2] = 0, false
    if (argv[2][0] == '1')
    {
        wait(NULL); // no se si el ejercicio me está pidiendo esto
    }

    pid_child1 = fork();

    if (pid_child1 == 0)
    {
        execlp("./child2", argv[1], NULL);
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
            printf("El proceso %d termina con exit code %d\n", getpid(), exitstat);
        }

        if (WIFSIGNALED(stat))
        {
            psignal(WTERMSIG(stat), "Forzando cierre del proceso");
        }
    }
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>
#define MAX 50

void main(int argc, char *argv[])
{
    int num, pid, child_pid, exitstat, stat, wait_thispid;
    bool bg = false;
    char cmd[MAX];
    bool background = false;

    while (1)
    {
        num = scanf("%s", cmd);
        // inserta comanda i la guarda a la variable cmd

        if (strcmp(cmd, "exit") == 0)
        {
            exit(0);
        }
    
        if (cmd[num - 1] == '&')
        {
           // printf("\npre: %c\n", cmd[num]);
            cmd[num - 1] = '\0'; // eliminem &
            bg = true;
        }
        else
        {
            bg = false;
        }
        
        pid = fork();
        if (pid == 0)
        {
            child_pid = getpid();
            if (bg)
            {
                printf("\nExecutant en bg %s amb PID = %d\n", argv[0], child_pid);
                wait_thispid = child_pid;
            }
            if (!bg)
            {
                printf("\nExecutant %s amb PID = %d\n", argv[0], child_pid);
            }

            execlp(cmd, cmd, NULL);
        }
        else
        {
            if (bg)
            {
                while (wait(&stat) > 0)
                {
                    if (WIFEXITED(stat))
                    {
                        exitstat = WEXITSTATUS(stat);
                        // en el caso de que en WEXITSTATUS(stat) yo reciba un 0, todo ha ido bien, si stat recibe un 255 significará que el exit de replicant ha sido -1
                        if (exitstat == 255)
                        {
                            exitstat = -1;
                        }
                        printf("El proceso %d termina con exit code %d\n", child_pid, exitstat);
                    }
                    if (WIFSIGNALED(stat))
                    {
                        psignal(WTERMSIG(stat), "Forzando cierre del proceso");
                    }
                }
            }
            else
            {
                while (wait(&stat) > 0)
                {
                    if (WIFEXITED(stat))
                    {
                        exitstat = WEXITSTATUS(stat);
                        // en el caso de que en WEXITSTATUS(stat) yo reciba un 0, todo ha ido bien, si stat recibe un 255 significará que el exit de replicant ha sido -1
                        printf("El proceso %d termina con exit code %d\n", child_pid, exitstat);
                        
                    }
                }
            }

            /*
             while ((waitpid(child_pid ,&stat, WNOHANG) > 0))
             {

                 if (WIFEXITED(stat))
                 {
                     exitstat = WEXITSTATUS(stat);
                     // en el caso de que en WEXITSTATUS(stat) yo reciba un 0, todo ha ido bien, si stat recibe un 255 significará que el exit de replicant ha sido -1
                     if (exitstat == 255)
                     {
                         exitstat = -1;
                     }
                     printf("El proceso %d termina con exit code %d\n", child_pid, exitstat);
                 }

             }
             */
        }
    }
}
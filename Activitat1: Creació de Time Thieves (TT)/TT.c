#include "checkparams.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void usage(char *str[])
{
    printf("\nUsage: el programa ha fallado, faltan parámetros. Ejemplo de uso: %s %s>0 %s>0\n", str[0], str[1], str[2]);
    exit(-1);
}

void main(int args, char *argv[])
{
    int i, m, n, pid, stat, exitstat;
    if (!checkparams(args, argv)) // función del archivo checkparams.h, proviene del ejercicio anterior
    {
        usage(argv);
    }
    else
    {
        if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0)
            usage(argv);
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    for (i = 0; i < m; i++)
    {
        pid = fork();

        // si pid = 0, se trata del hijo
        if (pid == 0)
        {
            execlp("./replicant", argv[2], NULL);
        }
    }

    // después de que se hayan ejecutado los hijos, el padre esperará a que terminen
    while ((wait(&stat) > 0))
    {
        
        if (WIFEXITED(stat))
        {
            exitstat = WEXITSTATUS(stat);
            // en el caso de que en WEXITSTATUS(stat) yo reciba un 0, todo ha ido bien, si stat recibe un 255 significará que el exit de replicant ha sido -1
            if (exitstat == 255)
            {
                printf("Estado de el proceso (exit): -1\n\n");
            }
            else
            {
                printf("Estado de el proceso (exit): %d\n\n", exitstat);
            }
        }

        if (WIFSIGNALED(stat))
        {
            psignal(WTERMSIG(stat), "Forzando cierre del proceso");
        }
    }
}
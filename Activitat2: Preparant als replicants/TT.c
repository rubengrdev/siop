#include "checkparams.h"
#include "dummy2.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define TEAMNAME "RUBENGOMEZ"
#define ENIGMA1 "chmod 760 codex"

void usage(char *str[])
{
    printf("\nUsage: el programa ha fallado, faltan parámetros. Ejemplo de uso: %s %s>0 %s>0<2000\n", str[0], str[1], str[2]);
    exit(-1);
}

void main(int args, char *argv[])
{
    int i, m, n, pid, stat, exitstat, acum = 0, fd;
    if (!checkparams(args, argv)) // función del archivo checkparams.h, proviene del ejercicio anterior
    {
        usage(argv);
    }
    else
    {
        if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[2]) > 2000)
            usage(argv);
    }

    fd = dummy_open();
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    for (i = 0; i < m; i++)
    {
        pid = fork();

        // si pid = 0, se trata del hijo
        if (pid == 0)
        {
            close(0); // cerramos entrada 0
            dup(fd); // hace que 0 apunte a fd
            execlp("./replicant", "replicant", argv[2], (char *)NULL);
        }
    }

    // después de que se hayan ejecutado los hijos, el padre esperará a que terminen
    while ((wait(&stat) > 0))
    {
        exitstat = WEXITSTATUS(stat);
        acum += exitstat;
    }
    dummy_test(acum, ENIGMA1, TEAMNAME);
}

// INFO
// para compilar: gcc TT.c -o TT -L. -ldummy

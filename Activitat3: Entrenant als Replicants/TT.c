#include "checkparams.h"
#include "dummy3.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define TEAMNAME "RUBENGOMEZ"
#define ENIGMA2 "grogu"        // insert between "" solution of enigna 2
#define BRONCEKEY "7a41e" // insert BRONCEKEY between ""

void usage(char *str[])
{
    printf("\nUsage: el programa ha fallado, faltan parámetros. Ejemplo de uso: %s %s>0 %s>0<2000\n", str[0], str[1], str[2]);
    exit(-1);
}

void main(int args, char *argv[])
{
    int i, m, n, pid, stat, exitstat, acum = 0, fd, canal_pipe[2];

    if (!checkparams(args, argv)) // función del archivo checkparams.h, proviene del ejercicio anterior
    {
        usage(argv);
    }
    else
    {
        if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[2]) > 2000)
            usage(argv);
    }

    fd = open("dummy.dat", O_RDONLY);
    dummy_checkfile(fd);
    m = atoi(argv[1]);
    n = atoi(argv[2]);

    // Crea pipe
    pipe(canal_pipe);
    // recibe señal del capitol
    signal(SIGUSR1, ready);
    
    pid = fork();
    /*Crea capitol*/
    if ((pid = fork()) == 0)
    {
        close(0);
        dup(fd);
        close(fd);
        close(1);
        dup(4); //canal pipe r
        close(4);   //canal_pipe[0] r 
        close(5);      //canal_pipe[1] w
        execlp("./capitol", "capitol", (char *)NULL);
    }
    else
    {

        for (i = 0; i < m; i++)
        {
            pid = fork();

            // si pid = 0, se trata del hijo
            if (pid == 0)
            {
                close(0); // cerramos entrada 0
                dup(4);  // hace que 0 apunte a canal_pipe[0] = r
                close(4);
                close(5);
                close(fd);
                execlp("./replicant", "replicant", argv[2], (char *)NULL);
            }
        }
    }
    // después de que se hayan ejecutado los hijos, el padre esperará a que terminen
    while ((wait(&stat) > 0))
    {
        exitstat = WEXITSTATUS(stat);
        acum += exitstat;
    }
     dummy_testing(acum, ENIGMA2, TEAMNAME, BRONCEKEY);
}

// INFO
// para compilar: gcc TT.c -o TT -L. -ldummy

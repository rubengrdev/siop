#include "checkparams.h"
#include "dummy4.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define SERVNAME "SIOP-server"
#define SERVADDR "147.83.159.200"
#define SERVPORT 9999
#define CTRLPORT 9900
#define TEAMNAME "RUBENGOMEZ" // insert between "" your team name
#define ENIGMA3 ""            // insert between "" solution of enigna 3
#define SILVERKEY "ab15e"     // insert SILVERKEY between ""
#define GOLDKEY ""            // use only for SIOP Challenge : insert GOLDKEY between ""

void usage(char *str[])
{
    printf("\nUsage: el programa ha fallado, faltan parámetros. Ejemplo de uso: %s %s>0 %s>0<2000\n", str[0], str[1], str[2]);
    exit(-1);
}

void main(int args, char *argv[])
{
    int i, m, n, pid, stat, exitstat, acum = 0, fd, ctrlfd;
    int nbytes, len;
    char *buffy, *buf;
    if (!checkparams(args, argv)) // función del archivo checkparams.h, proviene del ejercicio anterior
    {
        usage(argv);
    }
    else
    {
        if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[2]) > 2000)
            usage(argv);
    }
    /*retorna el file descriptor del canal de control i verifica l'enigma i la clau*/
    ctrlfd = ctrlconnect(SERVADDR, CTRLPORT, ENIGMA3, TEAMNAME, SILVERKEY, GOLDKEY);
  printf("\nHola estoy aqui!!!");
    fd = connecta(SERVADDR, SERVPORT); /*retorna el file descriptor del canal de dades*/
  
    m = atoi(argv[1]);
    n = atoi(argv[2]);

    
    for (i = 0; i < m; i++)
    {
        pid = fork();

        // si pid = 0, se trata del hijo
        if (pid == 0)
        {
            execlp("./replicant", "replicant", argv[2], (char *)NULL);
        }
    }

    // después de que se hayan ejecutado los hijos, el padre esperará a que terminen
    while ((wait(&stat) > 0))
    {
        exitstat = WEXITSTATUS(stat);
        acum += exitstat;
    }

    nbytes = sprintf(buf, "%d", acum);
    write(ctrlfd, buf, nbytes);
    len = read(ctrlfd, buffy, 128);
    buffy[len] = '\0';
    printf("MISSION: %s\n", buffy);
}

// INFO
// para compilar: gcc TT.c -o TT -L. -ldummyX

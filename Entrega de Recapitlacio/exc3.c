#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
A continuaci´o escriu un fragment de codi que cre¨ı una seq¨u`encia de N
processos en cadena: cada proc´es pi crea un sol descendent p(i+1), fins
arribar a pN . Cada proc´es s’ha de comunicar en cadena amb l’ascendent i
el descendent mitjan¸cant una pipe pel canal d’E/S est`andard, de manera
que el que escrigui el primer proc´es pugui ´esser enviat en cadena fins al
darrer proc´es. Es una jerarquia de processos tipus pare, fill, net, besnet etc
... fins a N amb una pipe entre ells segons l’esquema de la figura seg¨uent.
Per la l´ınia de comandes s’indica el numero de fills a crear (N).
*/

void main(int argc, char *argv[])
{
    int N;
    // hi ha indicat els paràmetres correctes i el numero de fills > 0
    if (argc == 2 && (N = atoi(argv[1])) > 0)
    {
        int pipe_fd[2];

        printf("\nPID Pare: %d\n", getpid());

        for (int i = 0; i < N; ++i)
        {
            pid_t pid = fork();
            //procés pare: 
            if (pid > 0)
            {
                // Proceso padre
                printf("Proces pare: %d crea un fill %d.\n", getpid(), pid);
                close(pipe_fd[1]);

                // Lectura desde la pipe
                int value;
                read(pipe_fd[0], &value, sizeof(value));

                printf("Proces pare: %d reb el valor %d del seu fill amb PID: %d\n", getpid(), value, pid);

                close(pipe_fd[0]);

                // Esperem a que el fill acabi:
                wait(NULL);
                exit(EXIT_SUCCESS);
            }
            else
            {
                // Fill
                close(pipe_fd[0]);

                // Escriptura a la pipe
                int value = i + 1;
                write(pipe_fd[1], &value, sizeof(value));
                printf("\nProces fill: %d envia el valor %d a su pare %d\n\n", getpid(), value, getppid());

                close(pipe_fd[1]);
            }
        }
    }
    else
    {
        printf("\nNúmero de paràmetres incorrecte");
    }
}
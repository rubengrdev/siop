#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void main(int argc, char *argv[])
{
    int N;
    // hi ha indicat els paràmetres correctes i el numero de fills > 0
    if (argc == 3 && (N = atoi(argv[2])) > 0)
    {
        /*
            argv[2] -> contingut per encriptar/desencriptar
            argv[3] -> numero de fills
        */

        int pipe_fd[2];

        for (int i = 0; i < N; ++i)
        {
            pid_t pid = fork();
            // procés pare:
            if (pid > 0)
            {
                // Proceso padre
                close(pipe_fd[1]);

                // Lectura desde la pipe
                char *value;
                read(pipe_fd[0], &value, strlen(value));

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
                execl("./exercici2", "exercici2", NULL);
                char *value = "";
                write(pipe_fd[1], &value, sizeof(value));
                close(pipe_fd[1]);
            }
        }
    }
    else
    {
        printf("\nNúmero de paràmetres incorrecte");
    }
}

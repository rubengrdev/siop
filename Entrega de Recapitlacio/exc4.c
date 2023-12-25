#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 100

void main(int argc, char *argv[])
{
    if (argc != 4)
    {
        perror("Error en els arguments (args necessaris: 4)\n");
        exit(-1);
    }
    int n = atoi(argv[2]);
    int c_pipe[n][2];
    int pos;
    char str[MAX];
    int file_lectura;
    int file_escriptura;

    for (int i = 0; i < n; i++)
    {
        // inicia pipes
        pipe(c_pipe[i]);
        // només executa fills
        if (fork() > 0)
        {
            printf("Key: %d\n", getpid() % 10);
            if (i != 0)
            {
                pos = i - 1;
                dup2(c_pipe[pos][0], 0);
                close(c_pipe[pos][0]);
            }
            else
            {
                file_lectura = open(argv[1], O_RDONLY);
                dup2(file_lectura, 0);
                close(file_lectura);
            }
            if (i != n - 1)
            {
                dup2(c_pipe[i][1], 1);
                close(c_pipe[i][1]);
            }
            else
            {
                close(c_pipe[i][1]);
                close(c_pipe[i][0]);
                file_escriptura = open(argv[3], O_WRONLY);
                dup2(file_escriptura, 1);
                close(file_escriptura);
            }
            // final redirect sortida
            execl("./encripta", "./encripta", NULL);
        }
    }
    exit(0);
}
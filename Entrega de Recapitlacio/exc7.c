#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>
#define MAX 100

void main(int argc, char *argv[])
{
    if (argc != 4)
    {
        perror("Error en els arguments (args necessaris: 4)\n");
        exit(-1);
    }
    int n;
    if (n = atoi(argv[2]) <= 0)
    {
        perror("Error en els arguments son incorrectes\n");
        exit(-1);
    }

    int c_pipe[n][2];
    int counter[2];
    char str[MAX];
    char str_ac[sizeof(int)];
    unsigned int rollback;
    int file_lectura;
    int file_escriptura;

    pipe(counter);
    write(counter[1], str_ac, sizeof(str_ac));

    for (int i = 0; i < n; i++)
    {
        rollback = i - 1;
        pipe(c_pipe[i]);
        if (fork() > 0)
        { 
            write(1, str, strlen(str));
            read(counter[0], str_ac, strlen(str_ac));
            sprintf(str_ac, "%d", atoi(str_ac) + getpid() % 10);
            write(counter[1], str_ac, strlen(str_ac));
            if (i != 0)
            {
                dup2(c_pipe[i - 1][0], 0);
                close(c_pipe[i - 1][0]);
            }
            else
            {
            }
            file_lectura = open(argv[1], O_RDONLY);
            dup2(file_lectura, 0);
            close(file_lectura);

            if (i != n - 1)
            {
                dup2(c_pipe[i][1], 1);
            }
            else
            {
                close(c_pipe[i][0]);
                file_escriptura = open(argv[3], O_WRONLY);
                dup2(file_escriptura, 1);
                close(file_escriptura);
            }
            close(c_pipe[i][1]);
            execl("./encripta", "./encripta", NULL);
        }
        wait(NULL);
    }
    file_lectura = open(argv[3], O_RDONLY);
    dup2(file_lectura, 0);
    read(counter[0], str_ac, sizeof(str_ac));
    execl("./desencripta", "./desencripta", &str_ac, NULL);
    exit(0);
}
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"
#include "sys/wait.h"

#define N 3

void procesar()
{
    char c;
    while (read(0, &c, sizeof(char)) > 0)
        write(1, &c, sizeof(char));
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd_ent, fd_sort;
    int pids[N];
    int i = 0;
    if ((fd_ent = open("in.txt", O_RDONLY)) < 0)
        perror("Error al primer open ");
    if ((fd_sort = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 777)) < 0)
        perror("Error al segon open ");
    for (i = 0; i < N; i++)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            /* open("in.txt" .... */
            /* open("out.txt" .... */
            dup2(fd_ent, 0);
            dup2(fd_sort, 1);
            procesar();
        }
    }
    close(fd_ent);
    while (waitpid(-1, NULL, 0) > 0);
}
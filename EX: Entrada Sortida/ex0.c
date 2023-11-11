#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wait.h>

void main()
{
    int fd1, fd2, fd3;
    int pid1, pid2, stat, i;

    fd1 = open("s1.txt", O_WRONLY | O_CREAT, 640);
    write(fd1, "p", sizeof(char));
    if ((pid1 = fork()) == -1) printf("\nerror");
    if (pid1 == 0) /* fill */
    {
        fd2 = open("s2.txt", O_WRONLY | O_CREAT, 640);
        for (i = 0; i < 5; i++)
        {
            if ((pid2 = fork()) == 0) /* net */
            {
                fd3 = open("s1.txt", O_WRONLY);
                write(fd1, "n", sizeof(char));
                write(fd2, "n", sizeof(char));
                write(fd3, "n", sizeof(char));
                close(fd1);
                close(fd2);
                close(fd3);
                exit(0);
            }
        }
        for (i = 0; i < 5; i++)
            wait(&stat);
        write(fd1, "h", sizeof(char));
        write(fd2, "h", sizeof(char));
        close(fd1);
        close(fd2);
        exit(0);
    }
    wait(&stat);
    write(fd1, "p", sizeof(char));
    close(fd1);
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
//@pre entrada tipus myshell cmd1 cmd2 cmd3
void main()
{

    int num, pid, stat, exitstat, returnstat;
    char *bg;
    char cmd[MAX];
    char *array;
    printf("Indica la teva comanda (sense arguments): ");
    scanf("%s", cmd);
    num = strlen(cmd);
    // inserta comanda i la guarda a la variable cmd

    if (cmd[num-1] == '&')
    {
        cmd[num - 1] = '\0'; // eliminem &
        bg = "1\0";
    }
    else
    {
        bg = "0\0";
    }
   
    //printf("\n%s", array[1]);
    pid = fork();
    if (pid == 0)
    {
        // execlp("./child", cmd, NULL);
         execv("./child", (char*[]){"child",cmd,bg, NULL});
    }

    while ((wait(&stat) > 0))
        ;
}
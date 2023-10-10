#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#define MAX 50

int main()
{
    int num, specPid, status;
    pid_t pid;
    char cmd[MAX];
    num = scanf("%s", cmd);
    pid = fork();
    // procés fill
    if (pid == 0)
    {
        specPid = getpid();
    }

    if (pid > 0)
    {
        printf("\nExecutant %s amb PID=%d...", cmd, specPid);
        kill(specPid, SIGTERM);
        sleep(1);
        waitpid(specPid, &status, WNOHANG);
        printf("\nEl proceso %d termina con exit code %d", specPid, status);
    }
    else
    {
        char *args[] = {cmd, NULL};
        execvp(cmd, args);
    }
}
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int pid1, pid2, fd[2];
	char s1[] = "izquierda";
	char s2[] = "derecha";

	if (argc!=2){ 
		printf("Paràmetres incorrectes\n");
		exit(-1);
	}

	if ((pid1=fork()) > 0) pid2 =fork();

	if (pid1 == 0)
	{
		if (strcmp(argv[1],s1) == 0) kill(getppid(), SIGKILL);
		else while(1);
		printf("He matat al meu pare\n");
		exit(-1);
	}

	if (pid2 == 0)
	{
		if (strcmp(argv[1],s2)==0)
			kill(pid1, SIGKILL);
		else while(1);
		printf("He matat al meu germa1\n");
		exit(-1);
	}

	wait(NULL);
	wait(NULL);
	exit(0);
}

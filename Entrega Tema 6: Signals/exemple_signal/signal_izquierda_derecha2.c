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
        pipe(fd);

	if ((pid1=fork()) > 0){
 		pid2 =fork();
		write(fd[1],&pid2,sizeof(int));
		close(fd[0]);close(fd[1]);
	}
	else if (pid1 == 0)
	{	close(fd[1]);
		if(read(fd[0],&pid2,sizeof(int))<0) perror("Error al llegir de la pipe\n");
		close(fd[0]);
		if (strcmp(argv[1],s1) == 0) kill(pid2, SIGKILL);
		else while(1);
		printf("He matat al meu germa 2 %d \n",pid2);
		exit(-1);
	}

	if (pid2 == 0)
	{
		close(fd[0]);close(fd[1]);
		if (strcmp(argv[1],s2)==0)
			kill(pid1, SIGKILL);
		else while(1);
		printf("He matat al meu germa1 %d \n",pid1);
		exit(-1);
	}

	wait(NULL);
	wait(NULL);
	printf("Soc el pare ...: %d", getpid());
	exit(0);
}

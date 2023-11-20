#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80

int main (int argc, char *argv[]){

	int fd1[2],fd2[2];
	int i;
	pid_t pid1, pid2;
	pid_t pid_germa,pid_meu;
	char tmp[MAX];

	pipe(fd1);
	pipe(fd2);
	if((pid1=fork())>0){ /* pare */
		if((pid2=fork())>0){ /* pare */
			// tanca tots els canals de les pipes
			close(fd1[0]);close(fd1[1]);
			close(fd2[0]);close(fd2[1]);
			while(waitpid(-1,NULL,WNOHANG)>0);
			exit(0);
		}else{ /*fill2 */
			// Preparo lectura, redireccio de fd1[0] al 0
			close(0); dup(fd1[0]);
			close(fd1[0]);close(fd1[1]);
			// Preparo escriptura redireccio de fd2[1] al 1
			close(1); dup(fd2[1]);
			close(fd2[0]);close(fd2[1]);

		}
	}else{ /* fill 1 */
		// Preparo lectura, redireccio de fd2[0] al 0
		close(0); dup(fd2[0]);
		close(fd2[0]);close(fd2[1]);
		// Preparo escriptura redireccio de fd1[1] al 1
		close(1); dup(fd1[1]);
		close(fd1[0]);close(fd1[1]);

	}
	/* Codi fills */
	pid_meu=getpid();
	write(1,&pid_meu,sizeof(pid_meu));
	if(read(0,&pid_germa,sizeof(pid_germa))>0){
		sprintf(tmp,"[%d] Pid_germa es %d\n",getpid(),pid_germa);
		write(2,&tmp,strlen(tmp));
	}

}

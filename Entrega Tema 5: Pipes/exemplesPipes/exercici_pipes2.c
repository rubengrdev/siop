#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 5


int main (int argc, char *argv[]){

	int fd[2];
	int i;
	pid_t childpid;
	int num_secret=7;

	for( i=0;i<N;i++){
		pipe(fd);
		if((childpid=fork())==0){ /* fill */
			/* redirecciona l'entrada estandard a la pipe */
			close(0); dup(fd[0]);
			close(fd[0]); close(fd[1]);
		}else{ /* pare */
			/* redirecciona la sortida estandard a la pipe */
			close(1); dup(fd[1]);
			close(fd[0]); close(fd[1]);
			break;
		}
	}
	if(read(0,&num_secret,sizeof(num_secret))>0){
		write(1,&num_secret,sizeof(num_secret));
	}
	wait(NULL);
}

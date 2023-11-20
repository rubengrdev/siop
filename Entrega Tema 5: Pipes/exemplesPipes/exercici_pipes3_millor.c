#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define N 5


int main (int argc, char *argv[]){

	int fd[N][2];
	int i,j;
	pid_t childpid;
	int father_pid=getpid();

	for( i=0;i<N;i++){
		pipe(fd[i]);
		if((childpid=fork())==0){ /* fill */
			dup2(fd[i][0],0);
			close(fd[i][0]); close(fd[i][1]);
			for(j=0;j<i;j++)
				close(fd[j][1]);
			break;
		}else{ /* pare */
			close(fd[i][0]);
		}
	}
	/* comprovem que funciona fent que el pare envii el seu pid a tots els fills */
	if(childpid==0){ /*fill */
			/* rebo el pid del pare */
			read(0,&father_pid,sizeof(father_pid));
			if(father_pid!=getppid())
				printf("%d: no he rebut pid del pare be %d:%d\n",getpid(),father_pid,getppid());
			exit(0);
	}else{ /* pare */
	/* per comprovar que funciona li escric el pid del pare al tots els fills */
		for( i=0;i<N;i++){
			write(fd[i][1],&father_pid,sizeof(father_pid));
			close(fd[i][1]);
		}
	}
	while(wait(NULL)>0);
}

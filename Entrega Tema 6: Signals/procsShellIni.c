#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#define MAX 10
// Funcio que procesa el codi del exit
void EscribeExitCode(int pid, int code)
{
	int statuscode,signcode;
	char buffer[90];
	if (WIFEXITED(code)){
		statuscode=WEXITSTATUS(code);
		sprintf(buffer,"El proceso %d termina con exit code %d\n",pid,statuscode);
		write(1,buffer,strlen(buffer));
	}else{
		signcode=WTERMSIG(code);	
		sprintf(buffer,"El proceso %d termina por el signal %d\n",pid,signcode);
		write(1,buffer,strlen(buffer));
	}
}


int main()
{
    char cmd[MAX];
    int num,pid;
    int len=0;
    char prompt='%';
    int exitcode;
    while(1)
    {
       write(1,&prompt,sizeof(char));
       num=scanf("%s",cmd);
       len=strlen(cmd);
       if (strcmp(cmd,"exit")==0)  break; //exit(0);
       pid=fork();
       if(pid==-1) perror("Error en fork()\n");
       if(pid==0)        //Al fill li encarreguem cmd
             {
               execlp(cmd,cmd,NULL);
               perror("Error en executar comanda\n");
               exit(0);        //En cas d'error, avisar i sortir
             }

     }
}

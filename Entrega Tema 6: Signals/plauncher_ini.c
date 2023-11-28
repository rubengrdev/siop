#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#define MIN_PARS 2

// Funcion que procesa el exit code
void EscribeExitCode(int pid, int code)
{
	int ret;
	char tmp[60];
	if (WIFEXITED(code)){
		ret=WEXITSTATUS(code);
		sprintf(tmp,"El proceso %d termina con exit code %d\n",pid,ret);
		write(2,tmp,strlen(tmp));
	}else{
		ret=WTERMSIG(code);	
		sprintf(tmp,"El proceso %d termina por el signal %d\n",pid,ret);
		write(2,tmp,strlen(tmp));
	}
}

// Funcion que escribe como se ejecuta el programa
void Usage()
{
	printf("Usage: plauncher  cmd [cmd]\n");
	exit(1);
}

// Funcion que crea un proceso hijo para ejecutar un comando
void LanzaComando(char *cmd)
{
	int pid;
	pid=fork();
	if (pid==0){
		// Cambiamos al ejecutable que nos piden
		
		if (execlp(cmd,cmd,(char *)0)<0){
			perror("Exec FAILS\n");
			exit(-1);
		}
	}else if (pid<0){
		// Este codigo lo ejecuta el padre, pq el fork ha fallado
		perror("FORK FALLA\n");
		exit(1);
	}
}
// Funcion principal
int main(int argc,char *argv[])
{
	int pid, exit_code,i,num_cmd;
	// Minimo 1 comando a ejecutar
	if (argc<MIN_PARS) Usage();
	// Tenemos (argc-1) comandos que ejecutar
	num_cmd=argc-1;
	for (i=0;i<num_cmd;i++){
		// Como hemos contado a partir del 0, los comandos 
		// estan en i+1
		LanzaComando(argv[i+1]);
		// Ejecucion en fg esperamos a cada comando
		//wait(NULL);
	}
	while((pid=wait(NULL))>0){
		printf("%d ha acabat aqui\n",pid);
	}
	printf("All Done\n");
	exit(0);
}

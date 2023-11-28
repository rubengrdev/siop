#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define MIN_PARS 2

/* El programa plauncher en ejecucion background haciendo la espera del hijo con el SIGCHLD */

// Funcion que procesa el exit code
void EscribeExitCode(int pid, int code)
{
	int ret;
	if (WIFEXITED(code)){
		ret=WEXITSTATUS(code);
		printf("El proceso %d termina con exit code %d\n",pid,ret);
	}else{
		ret=WTERMSIG(code);	
		printf("El proceso %d termina por el signal %d\n",pid,ret);
	}
}
// funcion de captura SIGCHLD
void fin_hijo (int s)
{
	int pid, exit_code;
	while ((pid=waitpid(0,&exit_code,0))>0){
		EscribeExitCode(pid,exit_code);
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
 	signal(SIGCHLD,fin_hijo);
	for (i=0;i<num_cmd;i++){
		// Como hemos contado a partir del 0, los comandos 
		// estan en i+1
		LanzaComando(argv[i+1]);
	}
	exit(0);
}

#include "dummy.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void usage(char*str)
{
    printf("\nUsage: el programa ha fallado, faltan parámetros. Ejemplo de uso: %s M N", str);
    exit(-1);
}

void main(int args, char *argv[])
{
    int i, m, n, pid, stat, exitcode;
    if (args < 3)
    {
        usage(argv[0]);
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    for(i = 0; i < m; i++){
        pid = fork();
        
        //si pid = 0, se trata del hijo
        if(pid == 0){
            execlp("./replicant", argv[2], NULL);
        }else{
            //después de que se hayan ejecutado los hijos, el padre esperará a que terminen
            while((wait(&stat) > 0));  
        }   
        
    }
}
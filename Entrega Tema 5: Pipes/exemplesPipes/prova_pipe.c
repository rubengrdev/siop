#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

int main (int argc, char *argv[]){

	int fd[2];
	int i,n,num;
	int tmp[MAX]={1,2,3,4};

	pipe(fd);
	for(i=0;i<MAX;i++){
		if((n=write(fd[1],&tmp[i],sizeof(int)))<0){
			perror("Error al write\n");
		}
	}
	for(i=0;i<MAX;i++){
		if((n=read(fd[0],&num,sizeof(int)))<0){
			perror("Error al read\n");
		}
		printf("Num %d\n",num);
	}

}

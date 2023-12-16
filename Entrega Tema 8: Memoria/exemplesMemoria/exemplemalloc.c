#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 3

/* Aquest programa mostra l'us de la routina de llibreria C malloc */
/* Mostra com malloc retorna un punter a la zona de memoria demanada */
/* La zona allocatada per un malloc es contigua en memoria */
/* pero si  fem 10 mallocs consecutius les 10 zones alocatades no tenen */
/* perque ser seguides, ens retorna un punter a cadascula d'elles */


int main (int argc, char *argv[])
{
  int i;
  int *ptr;
  int *ptr2[8];
	
  ptr = malloc(1024);
  printf("Primer malloc ptr %p  \n",ptr);

  for (i=0;i<8;i++){
	  ptr2[i] = malloc(128);
	  printf("Segundo malloc ptr2 %p \n", ptr2[i]);
  }

}

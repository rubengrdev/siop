#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 3

/* Aquest codi mostra l'us de la CAS sbrk */


int main (int argc, char *argv[])
{
  int i;
  int *new,*old;
  int *new2;
	
  old = sbrk(0); /*retorna el punt de break del programa */
  		/* El punt de break es on acaba la zona de heap */
  new = sbrk(1000); /* augmenta l'area de heap en 1000 bytes */
  		/* retorna el punt de break abans de la notificacio */
  new2 = sbrk(0);   /* consultem de nou el punt de break */
  		/* veiem que ha incrementat 1000 bytes */

  printf("Old %p  New %p new2 %p new2 %d\n",old,new,new2,new2);
  

}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 3

/* En aquest exemple es fa servir un punter
 * que ha estat alliberat  i per tant apunta a una zona
 * de la memoria que no tenim controlada i pot passar de tot:
 * pot ser que funcioni be (de vegades) o pot ser que 
 * aquesta memoria s'assigni a un altre proces i doni un error
 */


int main (int argc, char *argv[])
{
  int i;
  int *ptr;
  int *x;	

  ptr = malloc(128);
  printf("malloc ptr %p \n", ptr);

  x=ptr;

  free(ptr);

  printf(" x es %d\n",*x);
}

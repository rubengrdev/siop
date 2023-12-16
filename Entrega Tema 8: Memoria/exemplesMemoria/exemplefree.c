#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 3

/*  Aquest exemple allocata zones de memoria de 128 bytes 
 * 8 vegades, La primera observacio es que els punters que 
 * em retorna el malloc no necessariament son consecutius
 * La segona observacio es que aquest codi te un error perque
 * nomes allibera l'ultim punter i els altres no, i per tant crea
 * el que es coneix com a memory leak (que es un error molt dificil
 * de detectar). Es memoria que queda ocupada pero no esta en us
 * i com que hem perdut la variable amb el punter el proces no la pot 
 * alliberar. Desaprofita memoria i es dificil de detectar perque no
 * dona cap error, es detecta monitoritzant l'us de memoria dle proces.
 * En tercer lloc la crida free sobre un punter ja alliberat, el 
 * SO  envia un SIGABRT al nostre proces que atura la seva execucio
 * */


int main (int argc, char *argv[])
{
  int i;
  int *ptr;
	

  for (i=0;i<8;i++){
	  ptr = malloc(128);
	  printf("Segundo malloc ptr %p \n", ptr);
  }

  for (i=0;i<8;i++){
	free(ptr);
  }
}

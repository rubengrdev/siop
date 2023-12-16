#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>
int alarma = 0;
void error(char *msg)
{
  perror(msg);
  exit(0);
}

void f_alarma(int s)
{
  alarma = 1;
}

void main(int argc, char *argv[])
{
  int x, i;
  x = 0;
  int fd;
  char line, frase[20];
  bool busca_z = false;
  signal(SIGALRM, f_alarma);

  fd = open(argv[1], O_RDONLY);
  i = 0;
  while (read(fd, &line, 1) > 0)
  {
    if(i < 20) frase[i] = line;
    
    if(line == 'z'){
      busca_z = true;
    }
      //write(STDOUT_FILENO, &line, 1); // escricu per pantalla aquesta linea
    i++;
  }

  while (x < 10)
  {
    alarm(2);
    while (alarma == 0)
    {
      pause();
    }
    alarma = 0;
    if(busca_z){
      printf("\n%s",frase);
    }
    x++;
  }
}

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdio.h>
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
  int x, i, j = 0;
  x = 0;
  int fd;
  char line, frase[20];
  bool busca_z = false;
  signal(SIGALRM, f_alarma);

  fd = open(argv[1], O_RDONLY);
  i = 0;

  while ((read(fd, &line, 1) > 0) && !busca_z)
  {
    if (i < 20)
    {
      frase[i] = line;
    }
    else
    {
      // reset array
      while (j < i)
      {
        frase[j] = '\0';
        j++;
      }
      j = 0;
      i = -1;
    }

    if (line == 'z')
    {
      busca_z = true;
    }
    // write(STDOUT_FILENO, &line, 1); // escricu per pantalla aquesta linea

    i++;
  }
  alarm(2);
  while (alarma == 0)
  {
    pause();
  }
  alarma = 0;
  if (busca_z)
  {
    printf("\nHe trobat una z aquí:");
    printf("\n%s", frase);
  }else{
    printf("\nAlarma exhaurida");
    printf("\nNo he trobat cap z\n");
  }
}

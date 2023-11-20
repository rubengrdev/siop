#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX 4
int main(int argc, char *argv[])
{
   int fd[2], i, n, num = 0;
   int tmp[MAX] = {1, 2, 3, 4};
   pipe(fd);
   if (fork() == 0)
   {
      close(fd[0]);
      for (i = 0; i < MAX; i++)
      {
         if ((n = write(fd[1], &tmp[i], sizeof(int))) < 0)
         {
            perror("Error al write\n");
         }
      }
      close(fd[1]);
   }
   else
   {
      close(fd[1]);
      while ((n = read(fd[0], &num, sizeof(int))) > 0)
      {
         printf(" %d", num);
      }
      printf("\n");
      close(fd[0]);
   }
}

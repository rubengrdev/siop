#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char opcions(char lletra, unsigned int temp, int num_fill)
{
	if (num_fill == 0 && lletra == 'a')
	{
		lletra = 'e';
	}

	if (num_fill == 1 && lletra == 'c')
	{
		lletra = 'k';
	}

	if (num_fill == 2 && temp % 7 == 0)
	{
		write(1, &lletra, sizeof(char));
	}

	if (num_fill == 3 && lletra == 'm')
	{
		lletra = 'n';
	}
	if (num_fill > 4)
	{
		if (num_fill >= 10)
		{
			//de forma recursiva, si n_fill > 4, torna a començar al 1º fill i viceversa...
			opcions(lletra, temp, num_fill - 4);
		}
		
	}
	return lletra;
}

int main(int argc, char *argv[])
{

	int fd[2];
	char buf[255];
	int i = 0, num_fill;
	pid_t childpid;
	char c;
	unsigned int count_lletres;
	int lenght;
	for (i = 1; i <= atoi(argv[1]); i++)
	{
		pipe(fd); // pipe que controla el stdin
		if ((childpid = fork()) == 0)
		{ /* fill */
			/* redirecciona l'entrada estandard a la pipe */
			// prints del contador
			// sprintf(buf, "%d", i);
			// write(2, buf, strlen(buf));
			close(0);
			dup(fd[0]);
			count_lletres = 1;
			lenght = strlen(argv[1]);
			num_fill = i - 1;
			while (read(fd[0], &c, lenght) > 0)
			{
				c = opcions(c, count_lletres, num_fill);
				write(1, &c, sizeof(char));
				count_lletres++;
			}
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
		else
		{ /* pare */
			/* redirecciona la sortida estandard a la pipe */
			close(1);
			dup(fd[1]);
			close(fd[0]);
			close(fd[1]);
			// break;
		}
	}
	while (read(0, &c, sizeof(c)) > 0)
	{
		write(1, &c, sizeof(c));
	}
	wait(NULL);
}

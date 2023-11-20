#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char opcions(char lletra, unsigned int temp)
{

	if (lletra == 'a')
	{
		lletra = 'e';
	}

	if (lletra == 'c')
	{
		lletra = 'k';
	}

	if (temp % 7 == 0)
	{
		write(1, &lletra, sizeof(char));
	}

	if (lletra == 'm')
	{
		lletra = 'n';
	}
	return lletra;
}

int main(int argc, char *argv[])
{

	int fd[2];
	int i;
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
			close(0);
			dup(fd[0]);
			count_lletres = 1;
			lenght = strlen(argv[1]);

			while (read(fd[0], &c, lenght) > 0)
			{
				c = opcions(c, count_lletres);
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
			break;
		}
	}
	while (read(0, &c, sizeof(c)) > 0)
	{
		write(1, &c, sizeof(c));
	}

	wait(NULL);
}

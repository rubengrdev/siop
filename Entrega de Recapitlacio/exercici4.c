#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


/*
Un cop tenim l’esquema de processos i comunicaci´o entre ells creat, ara
volem que el primer proc´es llegeixi un fitxer, el nom del qual rebr`a per
la l´ınia de comandes, l’encripti (amb el programa que has escrit al primer
apartat) i el passi al seu descendent pel canal de comunicaci´o (pipe) que
hi ha entre ells. El proces numero 2 rebr`a el fitxer per la pipe l’encriptara
i el passara al seg¨uent proces escrivint-lo a la pipe que hi ha entre ells. I
aix´ı successivament fins al ultim proces que escriur`a el fitxer ben encriptat
(encriptat per tots els processos que l’han llegit) a un fitxer de sortida que
tamb´e rebr`a per la l´ınia de comandes. Es a dir, per la l´ınia de comandes
rebr`as (en aquest ordre) el fitxer d’entrada a encriptar (i.e. fitxer.txt), el
numero de processos a crear (i.e. 3) i el fitxer de sortida (encriptat) (i.e.
out.txt). A continuaci´o pots veure com hauria de funcionar el programa:

bash-3.2$ cat fitxer.txt
Bon dia
bash-3.2$ ./encripta-cadena fitxer.txt 3 out.txt
Key: 7
Key: 8
bash-3.2$ Key: 9
Key: 0
bash-3.2$ ls -la out.txt
-rw-rw-rw- 1 montsefarreras staff 13 24 Jan 12:56 out.txt
bash-3.2$ cat out.txt
8|y")mrjbash-3.2$

Veiem que cada programa que encripta el fitxer ens mostra la seva clau
d’encriptaci´o amb el missatge Key: 7 etc. I al final s’ha creat un nou
fitxer out.txt que esta ben encriptat. Modifica el programa del apartat
anterior perque el programa es comporti de la manera descrita. Cal fer
l’encriptaci´o de cada proces fent servir el programa que has fet al primer
apartat (encripta)i fer la redirecci´o de canals pertinent abans de cridar
l’exec.
*/

void main(int argc, char *argv[])
{
    int N;
    // hi ha indicat els paràmetres correctes i el numero de fills > 0
    if (argc == 3 && (N = atoi(argv[2])) > 0)
    {
        /*
            argv[2] -> contingut per encriptar/desencriptar
            argv[3] -> numero de fills
        */

        int pipe_fd[2];
        
        for (int i = 0; i < N; ++i)
        {
            pid_t pid = fork();
            // procés pare:
            if (pid > 0)
            {
                // Proceso padre
                close(pipe_fd[1]);

                // Lectura desde la pipe
                char*  value;
                read(pipe_fd[0], &value, strlen(value));

                close(pipe_fd[0]);

                // Esperem a que el fill acabi:
                wait(NULL);
                exit(EXIT_SUCCESS);
            }
            else
            {
                // Fill
                close(pipe_fd[0]);

                // Escriptura a la pipe
                execl("./exercici1", "exercici1", NULL);
                char * value = "";
                write(pipe_fd[1], &value, sizeof(value));
                close(pipe_fd[1]);
            }
        }
    }
    else
    {
        printf("\nNúmero de paràmetres incorrecte");
    }
}

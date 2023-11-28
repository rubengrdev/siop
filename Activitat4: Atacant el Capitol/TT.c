#include "checkparams.h"
#include "dummy4.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define SERVNAME "SIOP-server"
#define SERVADDR "147.83.159.200"
#define SERVPORT 9999
#define CTRLPORT 9900
#define TEAMNAME "RUBENGOMEZ" // insert between "" your team name
#define ENIGMA3 "mandalorian" // insert between "" solution of enigna 3
#define SILVERKEY "ab15e"     // insert SILVERKEY between ""
#define GOLDKEY ""            // use only for SIOP Challenge : insert GOLDKEY between "0xdbe9e"

/*Instrucció per resoldre l'enigma: openssl enc -aes-256-cbc -d -in encrypted_message.txt -out decrypted.txt -iv $(cat iv.txt) -K $(cat clue.txt)
 */
void usage(char *str[])
{
    printf("\nUsage: el programa ha fallado, faltan parámetros. Ejemplo de uso: %s %s>0 %s>0<2000\n", str[0], str[1], str[2]);
    exit(-1);
}

void main(int args, char *argv[])
{
    int i, m, n, pid, stat, exitstat, acum = 0, fd, ctrlfd;
    int nbytes, len;
    char buffy[255], buf[255];

    /*retorna el file descriptor del canal de control i verifica l'enigma i la clau*/
    ctrlfd = ctrlconnect(SERVADDR, CTRLPORT, ENIGMA3, TEAMNAME, SILVERKEY, GOLDKEY);
    fd = connecta(SERVADDR, SERVPORT); /*retorna el file descriptor del canal de dades*/

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    for (i = 0; i < m; i++)
    {
        pid = fork();

        // si pid = 0, se trata del hijo
        if (pid == 0)
        {
            close(0);
            dup(fd);
            close(fd);
            execlp("./replicant", "replicant", argv[2], (char *)NULL);
        }
    }
    int8_t code;
    // después de que se hayan ejecutado los hijos, el padre esperará a que terminen
    while ((wait(&stat) > 0))
    {

        code = WEXITSTATUS(stat);
        exitstat = code;
        acum += exitstat;
    }

    nbytes = sprintf(buf, "%d", acum);
    write(ctrlfd, buf, nbytes);
    len = read(ctrlfd, buffy, 128);
    buffy[len] = '\0';
    printf("MISSION: %s\n", buffy);
}

// INFO
// para compilar: gcc TT.c -o TT -L. -ldummyX

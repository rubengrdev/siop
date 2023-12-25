#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <string.h>

#define ASCII 128
#define MAX 100

void child(int s)
{
    printf("Codi finalització de %d: 0", getpid());
}

char codifica_caracter(char c, int key)
{
    char new_c = (c + key) % ASCII;
    return new_c;
}

void main(int argc, char *argv[])
{
    char str[MAX];
    char *new_str;
    unsigned int mida_cadena;
    int key = getpid() % 10;
    signal(SIGCHLD, child); // avisem al pare que el fill ha acabat

    fgets(str, MAX, stdin); // Lee una línea completa
    mida_cadena = strlen(str) * sizeof(char);
    new_str = (char *)malloc(mida_cadena);
    strcpy(new_str, str); // copiem la cadena de una mida acotada
    // encripta el text
    for (int i = 0; i < mida_cadena; i++)
    {
        new_str[i] = codifica_caracter(new_str[i], key);
    }

    write(1, new_str, mida_cadena); // escriu el text encriptat

    free(new_str);

    kill(getppid(), SIGCHLD);
    //salt de linea per a millorar la visibilitat al terminal...
    printf("\n");
    exit(0);
}
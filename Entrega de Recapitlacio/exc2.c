#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define ASCII 128
#define MAX 100

char descodifica_caracter(char c, int key)
{
    char new_c = (c - key);
    if (new_c < 0)
        new_c = ASCII + c - key;
    return new_c;
}

void main(int argc, char *argv[])
{
    char lletra;
    if (argv[1] == NULL)
    {
        perror("Error: Falta la clau de desencriptacio\n");
        exit(-1);
    }

    while (read(0, &lletra, 1) > 0)
    {
        lletra = descodifica_caracter(lletra, atoi(argv[1]));
        write(1, &lletra, 1);
    }
    exit(0);
}

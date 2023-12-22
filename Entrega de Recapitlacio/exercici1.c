#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define ASCII 128

/*
Escriu un programa que llegeixi un text de l’entrada est`andard (teclat)
l’encripti sumant-li l’ultim digit del seu PID al codi ASCII de cada car`acter,
i escrigui el text encriptat per la sortida est`andard El programa tamb´e cal
que escrigui la clau D’encriptaci´o (en aquest cas l’´ultim digit del seu PID
per la sortida est`andard d’error (pantalla).
Pots fer servir la funci´o que es
detalla a continuaci´o dins el teu programa per encriptar cada car`acter:

char codifica_caracter(char c, int key){
char new_c= (c + key)%ASCII;
return new_c;
}
*/


char codifica_caracter(char c, int key)
{
    char new_c = (c + key) % ASCII;
    return new_c;
}

void main(int argc, char *argv[])
{
    char *c;
    int pid = getpid();
    unsigned int key = 0;
    unsigned int mida_cadena;
    /*ja que el pid pot ser molt gran, fem modul a 10, així queda un número en forma d'unitat...*/
    key = pid % 10;
    do
    {
        key = pid % 10;
    } while (key == 0); // si el pid és 0, la cadena no serà encriptada, i aixó no es correcte

    mida_cadena = (sizeof(argv[1]) * sizeof(char));
    // reserva memoria per la cadena (màxima de 100 caràcters), es pot modificar al header de l'arxiu
    c = (char *)malloc(mida_cadena);

    strcpy(c, argv[1]);
    // encripta el text
    for (int i = 0; i < sizeof(c); i++)
    {
        c[i] = codifica_caracter(c[i], key);
    }
    // escriu el text encriptat
    printf("\nCadena encriptada: %s", c);

    // clau d'encriptacio:
    printf("\nKey: %d\n", key);
}

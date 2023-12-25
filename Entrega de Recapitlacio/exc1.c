#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define ASCII 128
#define MAX 100
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

int main(int argc, char *argv[])
{
    char str[MAX];
    char *new_str;
    unsigned int mida_cadena;
    int key = getpid() % 10;
    
    fgets(str, MAX, stdin);  // Lee una línea completa
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
    printf("\nKey: %d\n", key);
    return 0;
}
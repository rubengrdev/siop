#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define ASCII 128

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
    unsigned int key;
    int file;
    int mida_arxiu;
    int i;
    char *contingut;

    if(argc != 3){
        perror("Error en els arguments (args necessaris: 3)\n");
        exit(-1);
    }

    key = atoi(argv[1]);
    file = open(argv[2], O_RDONLY); //donem per suposat que les dades son correctes

    mida_arxiu = lseek(file, 0, SEEK_END);
    lseek(file, 0, SEEK_SET);


    //reserva espai per a contenir la data de l'arxiu:
    contingut = malloc(mida_arxiu * sizeof(char));
    //lectura de l'arxiu:
    read(file, contingut, mida_arxiu);
    close(file);    //tanca arxiu
    
    //imprimeix el contingut obtigut de l'arxiu:
    for(i = 0; i < mida_arxiu; i++){
        contingut[i] = descodifica_caracter(contingut[i], key);
    }

    write(1, contingut, mida_arxiu);
    free(contingut);
    //d'aquesta forma nomes hem fet 2 accesos al disc, tot ha sigut tractat amb la variable contignut una vegada copiada l'informació de l'arxiu
    //un acces per obrir l'arxiu i un altre per llegir-ho
    exit(0);
}
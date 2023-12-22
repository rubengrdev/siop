    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define ASCII 128
    #define MAX 100

    /*
    Escriu un programa que faci la funci´o contraria, es a dir desencriptar un
    fitxer. El programa rebr`a la clau d’encriptaci´o/desencriptacio per la l´ınia
    de comandes. El programa ha de llegir un text encriptat per l’entrada
    est`andard i escriure el text desencriptat per la sortida estandard. Pots
    fer servir la funci´o que et detallo a continuaci´o dins el teu programa per
    desencriptar cada car`acter:

    char descodifica_caracter(char c, int key){
    char new_c =(c-key);
    if (new_c<0) new_c = ASCII+c -key;
    return new_c;
    }

    Pots provar el teu programa redireccionant la sortida est`andard de en-
    cripta cap a un fitxer ( out.txt al exemple). Quan cridis al programa des-
    encripta haur`as de passar-li la clau ( Key) que ha impr`es el programa en-
    cripta i redireccionar l’entrada est`andard de desencripta al fitxer (out.txt).
    A continuaci´o es detalla un exemple d’execuci´o dels programes:

    bash-3.2$ ./encripta >out.txt
    Hola bon dia
    Key: 9
    bash-3.2$ ./desencripta 9 <out.txt
    Hola bon dia

    Tamb´e pots escriure el text que vols encriptar dins un fitxer (fitxer.txt al
    exemple) i cridar el teu programa encripta redireccionant tamb´e l’entrada
    est`andard

    bash-3.2$ ./encripta <fitxer.txt >out.txt
    Key: 5
    */
    char descodifica_caracter(char c, int key)
    {
        char new_c = (c - key);
        if (new_c < 0)
            new_c = ASCII + c - key;
        return new_c;
    }

    void main(int argc, char *argv[])
    {
        char *c;
        unsigned int key = 0;
        unsigned int mida_cadena;
        //la clau és el primer paràmetre que reb el programa
        key = atoi(argv[1]);

        mida_cadena = (sizeof(argv[2]));
        // reserva memoria per la cadena (màxima de 100 caràcters), es pot modificar al header de l'arxiu
        c = (char *)malloc(mida_cadena);

        strcpy(c, argv[2]);
        // encripta el text
        for (int i = 0; i < strlen(argv[2]); i++)
        {
            c[i] = descodifica_caracter(c[i], key);
        }
        // escriu el text encriptat
        printf("\nCadena desencriptada: %s", c);

        // clau d'encriptacio:
        printf("\nKey: %d\n", key);
    }

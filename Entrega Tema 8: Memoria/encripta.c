#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

//Funcionament:
// 1. Passar per parametre el nom del fitxer
// 2. El programa llegeix el fitxer i el guarda en un string (tot això alocat dinamicament) amb malloc
// 3. El programa gira el string amb la funció girarString()
// 4. El programa mostra el string per pantalla
// 5. El programa allibera la memoria amb free


void girarString(char *texto) {
    int longitud = strlen(texto);

    for (int i = 0; i < longitud; i += 2) {
        // Verifica si hay al menos dos caracteres para girar
        if (i + 1 < longitud) {
            // Intercambia los caracteres en posición par e impar
            char temp = texto[i];
            texto[i] = texto[i + 1];
            texto[i + 1] = temp;
        }
    }
}


int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Usage: no se ha podido abrir el archivo.\n");
    }

    // Calcula el tamaño del archivo
    //així d'aquesta forma no he de recorrer el fitxer 2 vegades per emmagatzemar tot... altra forma seria recorrer tot el fitxer, contar els caràcters i després generar el malloc i posteriorment tornar a recorrer el fitxer per emmagatzemar tot    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Malloc, contem amb que la mida = tipus de dades*numero de dades
    char *file_content = (char *)malloc(file_size + 1);  
  

    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';  

    // Cierra el archivo
    fclose(file);

    girarString(file_content);

    // Muestra el contenido por pantalla
    printf("\n%s\n", file_content);

    // Libera la memoria asignada dinámicamente
    free(file_content);

    return 0;
}

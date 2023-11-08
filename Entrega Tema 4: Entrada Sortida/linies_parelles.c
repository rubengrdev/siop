#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


//executar ./linies_parelles nomarxiu.txt
void main(int argc, char *argv[])
{
    char *name, line;   //line equival a cada caracter de una linea
    int i = 0, fd, n;
    //obrim arxiu
    fd = open(argv[1], O_RDONLY);
    //iteració per l'arxiu
    while (read(fd, &line, 1) > 0)
    {
        if (line == '\n')
        {
            i++;    //conta cada salt de linea amb num linea = i
        }
        if (i % 2 == 0) //si residu de i/2 = 0, és un numero parell
        {
            write(STDOUT_FILENO, &line, 1); //escricu per pantalla aquesta linea
        }
    }
}

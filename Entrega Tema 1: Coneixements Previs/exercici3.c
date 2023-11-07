#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*l'exercici no especifica si he de considerar el limit als numeros enters (2147483647) o el seu extrem negatiu, aixi que nomes treballara dins d'aquests limits*/
int main(int argc, char *argv[])
{
    int item1, item2, sum;
    if (argc == 3)
    {
        /*recull l'entrada dels valors indicats per l'usuari*/
        item1 = atoi(argv[1]);
        item2 = atoi(argv[2]);
        sum = item1 + item2;
        printf("%d\n", sum);
    }
    else
    {
        printf("numero de parametres incorrectes\n");
    }
    return 0;
}

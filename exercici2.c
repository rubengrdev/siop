#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Interpreto l'exercici com que la mida del vector sempre sera la mateixa*/
#define midaArray 20

bool statsvector(int userInput)
{
    bool status = false;
    if (userInput >= 2 && userInput <= 20)
    { // no s'admeten mes de 20 numeros, i com decissio de disseny tampoc menys de 2, ja que no sera possible fer estadistiques amb sentit
        status = true;
    }
    else
    {
        printf("\nSi us plau, indica una quantitat de valors valida entre 2 i 20 per a poder fer el calcul");
    }
    return status;
}

int statistics(int *array, int *max, int *min, int userInput)
{
    int avg, j = 0, sumaArray = 0;
    /* @brief en aquest bucle obtindrem màxim, minim i mitjana,
     *  el max i min es comprovaran a cada iteració
     *  per aconseguir el avg nomes caldra fer una simple operacio matematica de suma i divisio */
    while (j < userInput)
    {
        // assignem el nou maxim i el nou minim
        if (array[j] > *max) *max = array[j];
        if (array[j] < *min) *min = array[j];
        sumaArray += array[j];
        j++;
    }
    avg = sumaArray / j;
    return avg;
}

int main(int argc, char *argv[])
{
    // vector de 20 elements, (elements aleatoris)
    int i = 0, j = 0, max, min, avg, userInput, array[] = {99, 50, 0, -24, 43, 23, 93, 71, 20, 0, 8, 103, 45, -1, 200, 43, 75, -2, 12, 43};

    if (argc == 2)
    {
        userInput = atoi(argv[1]); // assigna seleccio de items al vector
    }

    if (statsvector(userInput))
    {
        // inicia maxim i minim al mateix punt per començar a comprovar
        //(donem per suposat que l'array no serà vuit mai)
        max = array[0];
        min = array[0];

        // mostra el vector per pantalla
        printf("Contingut del vector: ");
        for (i = 0; i < midaArray; i++) printf("%d ", array[i]);
        avg = statistics(array, &max, &min, userInput);
        printf("\nmin: %d\nmax: %d \navg: %d\n", min, max, avg);
    }

    return 0;
}

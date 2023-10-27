#include <stdio.h>

/*Interpreto l'exercici com que la mida del vector sempre sera la mateixa*/
#define midaArray 20

int statistics(int *array, int *max, int *min)
{
    int avg, j = 0, sumaArray = 0;
    /* @brief en aquest bucle obtindrem màxim, minim i mitjana,
     *  el max i min es comprovaran a cada iteració
     *  per aconseguir el avg nomes caldra fer una simple operacio matematica de suma i divisio */
    while (j < midaArray)
    {
        // assignem el nou maxim i el nou minim
        if (array[j] > *max)
            *max = array[j];
        if (array[j] < *min)
            *min = array[j];
        sumaArray += array[j];
        j++;
    }
    avg = sumaArray / j;
    return avg;
}

int main()
{
    // vector de 20 elements, (elements aleatoris)
    int i = 0, j = 0, max, min, avg, array[] = {2, 3, 45, 6, 78, 2, 4, 9, 8, 7, 2, 23, 4, 56, 4, 5, 2, 3, 7, 9};
    //array[] = {99, 50, 0, -24, 43, 23, 93, 71, 20, 0, 8, 103, 45, -1, 200, 43, 75, -2, 12, 43};
    // inicia maxim i minim al mateix punt per començar a comprovar
    //(donem per suposat que l'array no serà vuit mai)
    max = array[0];
    min = array[0];

    // mostra el vector per pantalla
    printf("Contingut del vector: ");
    for (i = 0; i < midaArray; i++) printf("%d ", array[i]);

    avg = statistics(array, &max, &min);
    printf("\nmin: %d\nmax: %d \navg: %d\n", min, max, avg);
    return 0;
}

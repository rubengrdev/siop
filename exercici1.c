#include <stdio.h>

int main()
{
    // vector de 20 elements, (elements aleatoris)
    int i = 0, max, min, avg, sumaArray, num_elements = 20, array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 100};

    // inicia maxim i minim al mateix punt per començar a comprovar
    //(donem per suposat que l'array no serà vuit mai)
    max = array[0];
    min = array[0];
    /* @brief en aquest bucle obtindrem màxim, minim i mitjana,
     *  el max i min es comprovaran a cada iteració
     *  per aconseguir el avg nomes caldra fer una simple operacio matematica de suma i divisio
     */
    while (i < num_elements)
    {
        // assignem el nou maxim i el nou minim
        if (array[i] > max) max = array[i];
        if (array[i] < min) min = array[i];
        sumaArray += array[i];
        i++;
    }
    avg = sumaArray / num_elements;

    printf("\nmin: %d\nmax: %d \navg: %d\n", min,max,avg);
    return 0;
}
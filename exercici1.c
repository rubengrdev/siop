#include <stdio.h>



int statistics(int *array, int max, int min){
    int avg, j = 0, k = 0, sumaArray = 0;
    printf("\n\n%d", j);
   
    //  to do, recorrer el array y encontrar el tamaño desead
    

      /* @brief en aquest bucle obtindrem màxim, minim i mitjana,
     *  el max i min es comprovaran a cada iteració
     *  per aconseguir el avg nomes caldra fer una simple operacio matematica de suma i divisio
     */
    while (k < j)
    {
        // assignem el nou maxim i el nou minim
        if (array[k] > max) max = array[k];
        if (array[k] < min) min = array[k];
        sumaArray += array[k];
        k++;
    }
    avg = sumaArray / j;
}

int main()
{
    // vector de 20 elements, (elements aleatoris)
    int i = 0, j = 0, max, min, avg, midaArray = 20, array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 100};

    // inicia maxim i minim al mateix punt per començar a comprovar
    //(donem per suposat que l'array no serà vuit mai)
    max = array[0];
    min = array[0];
    
    //mostra el vector per pantalla
    printf("Contingut del vector: ");
    for(i=0; i < midaArray; i++) printf("%d ", array[i]);

    avg = statistics(array, max, min);
    //printf("\nmin: %d\nmax: %d \navg: %d\n", min,max,avg);
    return 0;
}


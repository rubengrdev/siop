
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy3.h"

int main(int args, char *argv[])
{

    int N = atoi(argv[1]), MAX_BUFFER = 2000, bytes_leidos = 0, dummy_cmp = 0;
    char *buffer;

    if (N > 0 && N <= MAX_BUFFER)
    {
        buffer = malloc(sizeof(char) * N);
        // comprovacions inicials
        dummy_init(buffer, N);
        bytes_leidos = read(0, buffer, N);
        while (bytes_leidos > 0)
        {
            // bytes_leidos tiene que ser igual a N, de lo contrario no funcionará la comparativa
            if (bytes_leidos > 0)
            {
                dummy_cmp = dummy_calc(buffer, bytes_leidos);
                printf("\nBytes Leidos: %d, N: %d", bytes_leidos, N);
            }
            bytes_leidos = read(0, buffer, N);
        }
        dummy_end();
    }
    else
    {
        exit(-1);
    }
}

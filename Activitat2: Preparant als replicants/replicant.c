
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy2.h"

int main(int args, char *argv[])
{

    int N = atoi(argv[0]), MAX_BUFFER = 2000, bytes_leidos, dummy_cmp;
    char *buffer;
    bool final = false;
    // printf("\nreplicant.c, N =%d", atoi(argv[0]));
    if (N >= 0 && N <= MAX_BUFFER)
    {
        buffer = malloc(sizeof(char) * N);
        // comprovacions inicials
        dummy_init(buffer, N);
        while (bytes_leidos > 0)
        {
            bytes_leidos = read(0, buffer, N);
            dummy_cmp = dummy_comp(buffer, N);
        }
        
        dummy_exit();
    }
}

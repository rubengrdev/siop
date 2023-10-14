#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy.h"


int main(int args, char *argv[])
{

    int N = atoi(argv[0]), MAX_BUFFER = 2000;
    char *buffer;
    bool final = false;
    //printf("\nreplicant.c, N =%d", atoi(argv[0]));
    if (N >= 0 && N <= MAX_BUFFER)
    {
        buffer = malloc(sizeof(char)*N);
        // comprovacions inicials
        dummy_ini(buffer, N);
        while (!final)
        final = dummy_cpt(buffer, N);
        dummy_end();
        exit(0);
    }
    else
    {
        exit(-1);
    }
}
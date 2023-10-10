#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy.h"

int main(int args, char *argv[])
{

    int N = atoi(argv[0]);
    char buffer[N];
    bool final = false;
    //printf("\nreplicant.c, N =%d", atoi(argv[0]));
    if (N > 0)
    {
        // comprovacions inicials
        dummy_ini(buffer, N);
        while (!final)
        final = dummy_cpt(buffer, N);
        dummy_end();
         printf("\n");
        exit(0);
    }
    else
    {
        exit(-1);
    }
}
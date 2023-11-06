
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy2.h"

int main(int args, char *argv[])
{

    int N = atoi(argv[1]), MAX_BUFFER = 2000, bytes_leidos = 1, dummy_cmp = 0;
    char *buffer;

    if (N > 0 && N <= MAX_BUFFER)
    {
        buffer = malloc(sizeof(char) * N);
        // comprovacions inicials
        dummy_init(buffer, N);

        while (bytes_leidos > 0)
        {
            bytes_leidos = read(0, buffer, N);
             printf("\nbytes leidos: %d & N: %d", bytes_leidos, N);
            if(bytes_leidos != 0){
                dummy_cmp = dummy_comp(buffer, N);
                printf(".....OK");
            }else{
                printf(".....NO");
            }
            
            
        }

        dummy_exit();
    }
    else
    {
        exit(-1);
    }
}

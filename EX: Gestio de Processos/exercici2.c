#include <stdio.h>

void main(int args, char* argv[]){
    int i;
    printf("\nArxius: ");
    for(i = 0; i < args; i++){
        printf("\n%s", argv[i]);
    }
    
}
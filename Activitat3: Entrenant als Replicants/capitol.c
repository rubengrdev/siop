#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy3.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dummy3.h"
#include <signal.h>

int main()
{
    int c;
    kill(getppid(), SIGUSR1);
    while (read(0, &c, 1) > 0){
        write(1, &c, 1);
    }
    exit(0);
}
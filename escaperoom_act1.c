#include <stdio.h>
#include <stdlib.h>
#define N 5

void question4()
{
    int i = 0;
    int f = 1;
    for (i = N; i > 0; i--)
        f = f * i;
    printf("\n%d", f);
}

void question5()
{
    int i = 0;
    int s = 0;
    int v[N] = {1, 2, 3, 4, 5};
    for (i = 0; i < N; i++)
        s = s + v[i];
    printf("s: %d \n", s);
}

void question7(int argc, char *argv[])
{
    int i = 0, n = 0, s = 0;
    if (argc == 2)
    {
        n = atoi(argv[1]);
    }
    else
    {
        n = 5;
    }
    for (i = 0; i <= n; i++)
    {
        s = s + i;
    }
    printf("s: %d\n", s);
}

int main(int argc, char *argv[])
{

    return 0;
}
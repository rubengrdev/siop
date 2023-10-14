#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

/*Comrpueba si la cadena insertada es valida (no acepta ningún valor que sea diferente de un numero entero)*/
bool checkString(char *str)
{
    bool status = true, exception = false;
    int i = 0;

    while (str[i] != '\0')
    {
        if ((str[i] < 48 || str[i] > 57))
        {
            status = false; // si el valor ascii de el caracter es diferente de el rango 48-57 significa que no es un numero entre 0 y 9, asi que podemos afirmar que no es un numero entero
            if ((i == 0 && str[i] == '-' && str[i + 1] != '0'))
            {
                status = true; // unico caso en el que permito valores diferentes, primer dígito = negativo, con excepción de que el siguiente número sea un 0, el -01 no debería ser valido para el tipo de formato que busco.
            }
        }
        i++;
    }
    return status;
}

/*Comprueba que los numeros indicados no sobrepasan las restricciones de los numeros enteros*/
bool checkLimits(char *num)
{
    bool limitOk = true;
    char *endptr;
    long long testNum = strtol(num, &endptr, 10);
    // si el puntero de el final del string no es igual a el 'centinela'/limite de string '/0' significa que no se ha podido hacer la conversion.
    if (*endptr != '\0' || testNum < INT_MIN || testNum > INT_MAX)
    {
        limitOk = false;
        // printf("\nHa sobrepasado el limite establecido");
    }
    return limitOk;
}

bool checkparams(int argc, char *argv[])
{
    bool result = false;
    // comprueba si el numero de parametros es correcto
    if (argc == 3)
    {
        // comprueba los valores insertados por el usuario
        if (checkString(argv[1]) && checkString(argv[2]))
        {
            if (checkLimits(argv[1]) && checkLimits(argv[2]))
            {
                // todo correcto
                // printf("\nLos valores introducidos '%s', '%s' se han verificado como numeros enteros (INT). Correcto.\n", argv[1], argv[2]);
                result = true;
            }
            else
            {
                printf("\nUsage: Los numeros introducidos no son correctos. Verifique la longitud de los mismos. Más información en: https://learn.microsoft.com/es-es/cpp/c-language/cpp-integer-limits?view=msvc-170\n");
            }
        }
        else
        {
            // comunica que los datos no son validos
            printf("\nUsage: Los numeros introducidos no son correctos. Verifique que no haya caracteres o caracteres especiales diferentes de 0-9 (int) y tengan un formato correcto.\n");
        }
    }
    else
    {
        printf("\nUsage: Los parametros introducidos no son correctos. Ha introducido %d valores. Parametros necesarios: 3\n", argc);
    }
    return result;
}

#include "mathfuncs.h"
#include <stdio.h>

double square(double n)
{
    return n * n;
}

double cube(double n)
{
    return n * n * n;
}

int main()
{
    printf("Square : %lf", square(5));
    printf("Cube:%lf", cube(2));

    return 0;
}
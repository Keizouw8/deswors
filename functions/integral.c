#include "../global.h"
#include "derivative.c"

double integral(double a, double b, double (*f)(double)){
    unsigned int n = 10;
    double dx = (a - b)/n;

    double sum = 0;
    for(int i = 0; i <= n; i++){
        int multiplier = 2;

        if(i % 2 == 1) multiplier = 4;
        if(i == 0 || i == n) multiplier = 1;

        sum += multiplier * f(a + dx * i);
    }

    return sum * dx / 3;
}
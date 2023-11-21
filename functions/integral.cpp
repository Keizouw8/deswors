#include "../global.hpp"
#include "derivative.hpp"
#include "max.hpp"
#include <math.h>
#include <functional>
#include <iostream>

double integral(double a, double b, const std::function<double(double)> &f, double accuracy = settings.graphing.reciprocal){
    if(a == b) return 0;
    if(a > b) return -integral(b, a, f);

    const double step = (b - a)/fmin(1.0e6, (b - a)*1.0e3);

    double k = max([f](double x) -> double{
        return fabs(nDeriv(4, x, f));
    }, a, b);
    if(k < 1) k = 1;

    unsigned int n = ceil(pow(fabs(k * pow(b - a, 5) / (180 * accuracy)), 0.25));
    if(n == 0) n = 2;
    if(n % 2 == 1) n++;
    double dx = (b - a)/n;

    double sum = 0;
    for(int i = 0; i <= n; i++){
        int multiplier = 2;

        if(i % 2 == 1) multiplier = 4;
        if(i == 0 || i == n) multiplier = 1;

        sum += multiplier * f(a + dx * i);
    }

    return sum * dx / 3;
}
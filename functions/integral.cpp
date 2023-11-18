#include "../global.hpp"
#include "derivative.hpp"
#include <math.h>

double integral(double a, double b, double (*f)(double)){
    if(a == b) return 0;
    if(a > b) return -integral(b, a, f);

    const double step = (b - a)/fmin(1.0e6, (b - a)*1.0e3);

    double k = 0;
    for(double i = a; i <= b; i += step){
        double temp = fabs(n_deriv(4, i, f));
        if(temp > k) k = temp;
    }

    unsigned int n = ceil(pow(fabs(k * pow(b - a, 5) / (180 * recip_acc)), 0.25));
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
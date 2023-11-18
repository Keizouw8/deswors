#include <math.h>

double derivative(double x, double (*f)(double)){
    const double delta = 1.0e-10;
    return (f(x + delta) - f(x - delta))/(2 * delta);
}

double n_deriv(unsigned int n, double x, double (*f)(double)){
    const double delta = 1.0e-4;
    if(n == 0) return f(x);
    return (n_deriv(n - 1, x + delta, f) - n_deriv(n - 1, x - delta, f))/(2 * delta);
}
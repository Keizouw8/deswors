#include <math.h>
#include <functional>

double derivative(double x, const std::function<double(double)> &f){
    const double delta = 1.0e-10;
    return (f(x + delta) - f(x - delta))/(2 * delta);
}

double nDeriv(unsigned int n, double x, const std::function<double(double)> &f){
    const long double delta = 1.0e-4;
    if(n == 0) return f(x);
    return (nDeriv(n - 1, x + delta, f) - nDeriv(n - 1, x - delta, f))/(2 * delta);
}
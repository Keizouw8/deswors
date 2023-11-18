#include "derivative.c"
#include <math.h>

double side_limit(int direction, double x, double (*f)(double)){
    if(!(direction == -1 || direction == 1)) return NAN;
    double dx = 1e-10;
    double off_x = x + direction * dx;
    return f(off_x) - (direction * dx * derivative(off_x, f));
}

double limit(double x, double (*f)(double)){
    double left = side_limit(-1, x, f);
    double right = side_limit(1, x, f);

    if(fabs(left - right) > 1e-5) return NAN;
    return (left + right)/2;
}
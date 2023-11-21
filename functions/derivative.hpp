#include <functional>

double derivative(double x, const std::function<double(double)> &f);
double nDeriv(unsigned int n, double x, const std::function<double(double)> &f);
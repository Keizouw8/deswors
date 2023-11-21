#include <functional>

double integral(double a, double b, const std::function<double(double)> &f, double accuracy=1);
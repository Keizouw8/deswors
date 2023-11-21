#include <functional>

double max(const std::function<double(double)> &f, double tl, double tu, double accuracy=1);
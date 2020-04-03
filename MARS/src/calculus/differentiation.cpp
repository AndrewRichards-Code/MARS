#include "differentiation.h"

using namespace mars;

double Differentiate(std::function<double(double)> function, double a, double h)
{
	return (function(a + h) - function(a)) / h;
}
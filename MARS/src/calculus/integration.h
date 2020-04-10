#pragma once
#include "../mars_common.h"

namespace mars
{
	double Integrate(std::function<double(double)> function, double a, double b, int h = 1000000);
}
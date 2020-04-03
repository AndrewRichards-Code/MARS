#pragma once

namespace mars
{
	static const double pi = 3.1415926535897932384626433832795;
	static const double tau = 2.0 * pi;

	//Coverts degrees to radians.
	inline double DegToRad(double angle)
	{
		return angle * pi / 180.0;
	}

	//Coverts radians to degrees.
	inline double RadToDeg(double angle)
	{
		return angle * 180.0 / pi;
	}
}
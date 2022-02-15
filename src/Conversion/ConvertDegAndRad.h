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

	//Coverts degrees to radians.
	inline float DegToRad(float angle)
	{
		return angle * static_cast<float>(pi) / 180.0f;
	}

	//Coverts radians to degrees.
	inline double RadToDeg(double angle)
	{
		return angle * 180.0 / pi;
	}

	//Coverts radians to degrees.
	inline float RadToDeg(float angle)
	{
		return angle * 180.0f / static_cast<float>(pi);
	}
}
#pragma once
#include "mars_common.h"

namespace mars
{
	struct CoordPolar;

	//Takes in an x and y for the coords.
	struct CoordCartesian2D
	{
		double x, y;
		CoordCartesian2D(double x, double y)
			:x(x), y(y) {}

		//Converts cartesian coordinates to polar coordinates.
		CoordPolar ToPolar() const;
	};
	
	//Takes in an r and theta(in radians) for the coords.
	struct CoordPolar
	{
		double r, theta;
		CoordPolar(double r, double theta)
			:r(r), theta(theta) {}

		//Converts spheric coordinates to cartesian coordinates.
		CoordCartesian2D ToCartesian2D() const;
	};
	
	inline CoordPolar CoordCartesian2D::ToPolar() const
	{
		double r, theta;
		r = sqrt(x * x + y * y);
		theta = atan2(y, x);
		return CoordPolar(r, theta);
	}

	inline CoordCartesian2D CoordPolar::ToCartesian2D() const
	{
		double x, y;
		x = r * cos(theta);
		y = r * sin(theta);
		return CoordCartesian2D(x, y);
	}
}
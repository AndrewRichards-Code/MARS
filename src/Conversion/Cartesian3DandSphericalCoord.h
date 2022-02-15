#pragma once
#include "mars_common.h"

namespace mars
{
	struct CoordSpherical;

	//Takes in an x, y and z for the coords.
	struct CoordCartesian3D
	{
		double x, y, z;
		CoordCartesian3D(double x, double y, double z)
			:x(x), y(y), z(z) {}

		//Converts cartesian coordinates to spherical coordinates.
		CoordSpherical ToSpherical() const;
	};

	//Takes in an r, theta(in radians) and phi(in radians) for the coords.
	struct CoordSpherical
	{
		double r, theta, phi;
		CoordSpherical(double r, double theta, double phi)
			:r(r), theta(theta), phi(phi) {}

		//Converts spheric coordinates to cartesian coordinates.
		CoordCartesian3D ToCartesian3D() const;
	};

	inline CoordSpherical CoordCartesian3D::ToSpherical() const
	{
		double r, theta, phi;
		r = sqrt(x * x + y * y + z * z);
		theta = acos(z / r);
		phi = atan2(y, x);
		return CoordSpherical(r, theta, phi);
	}

	inline CoordCartesian3D CoordSpherical::ToCartesian3D() const
	{
		double x, y, z;
		x = r * sin(theta) * cos(phi);
		y = r * sin(theta) * sin(phi);
		z = r * cos(theta);
		return CoordCartesian3D(x, y, z);
	}
}

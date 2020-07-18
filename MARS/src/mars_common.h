#pragma once

#include <ostream>
#include <iomanip>
#include <math.h>
#include <functional>

//Ostream Settings
namespace mars
{
	constexpr std::streamsize osFloatPrecision = 3;
	constexpr bool showPositiveSign = true;

	static inline void SetOstream(std::ostream& stream)
	{
		if (showPositiveSign)
			 stream << std::showpos;
		else
			stream << std::noshowpos;
		
		stream << std::setprecision(osFloatPrecision) << std::fixed;
	}

	static inline void ResetOstream(std::ostream& stream)
	{
		stream << std::noshowpos << std::defaultfloat;
	}
}

//Other
#include "conversion/ConvertDegAndRad.h"
#include "conversion/ConvertCart2DandPolarCoord.h"
#include "conversion/ConvertCart3DandSphCoord.h"

#include "matrix/Mat2.h"
#include "matrix/Mat3.h"
#include "matrix/Mat4.h"

#include "vector/Vec2.h"
#include "vector/Vec3.h"
#include "vector/Vec4.h"

#include "quaternion/Quat.h"

#include "calculus/differentiation.h"
#include "calculus/integration.h"

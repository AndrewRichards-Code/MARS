#pragma once

#include <ostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
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

#include "Conversion/ConvertDegAndRad.h"

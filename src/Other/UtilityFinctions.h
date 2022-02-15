#pragma once
#include "mars_common.h"

namespace mars
{
	class Utility
	{
	public:
		static bool IsPowerOf2(uint32_t x)
		{
			return !(x == 0) && !(x & (x - 1));
		}

		static uint32_t NextPowerOf2(uint32_t x)
		{
			x--;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			x++;
			return x;
		}
	};
}
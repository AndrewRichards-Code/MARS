#pragma once
#include "../mars_common.h"

namespace mars
{
	class Utility
	{
	public:
		static bool IsPowerOf2(uint32_t x);
		static uint32_t NextPowerOf2(uint32_t x);
	};
}
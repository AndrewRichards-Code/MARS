#include "UtilityFinctions.h"

using namespace mars;

bool mars::Utility::IsPowerOf2(uint32_t x)
{
	 return !(x == 0) && !(x & (x - 1));
}

uint32_t mars::Utility::NextPowerOf2(uint32_t x)
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

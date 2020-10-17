#include "UtilityFinctions.h"

using namespace mars;

bool mars::Utility::IsPowerOf2(uint32_t x)
{
	 return !(x == 0) && !(x & (x - 1));
}

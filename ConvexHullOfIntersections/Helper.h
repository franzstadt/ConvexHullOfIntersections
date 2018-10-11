#pragma once
#include <cmath>

namespace ConvexHull
{
	inline double round_4_decimal(double f) 
	{
		return std::round(f * 10000.0) / 10000.0;
	}
 }
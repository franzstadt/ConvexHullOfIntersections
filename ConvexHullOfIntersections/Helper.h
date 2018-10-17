#pragma once
#include "Constants.h"

#include <limits>
#include <cmath>


namespace ConvexHull
{
	inline double round_4_decimal(double f) 
	{
		return std::round(f * 10000.0) / 10000.0;
	}

	inline double Determinant(double a, double b, double c, double d) 
	{
		return a * d - b * c;
	}

	inline bool Equals(double a, double b)
	{
		return std::abs(a - b) <= std::numeric_limits<double>::epsilon() * std::abs(a + b) * 4.0 || std::abs(a - b) < std::numeric_limits<double>::min();
	}

	inline bool LE(double a, double b)
	{
		return a < b || Equals(a, b);
	}

	inline bool GE(double a, double b)
	{
		return a > b || Equals(a, b);
	}
 }
#pragma once
#include <cstdlib>

namespace ConvexHull
{
	struct Point
	{
		double x, y;
		Point(double px = 0.0, double py = 0.0);
		double distance(const Point& p2)  const;
		static bool Equals(double a, double b, double epsilon = 0.0001)
		{
			return std::abs(a - b) < epsilon;
		}
		bool operator==(const Point& rhs) const;
	};
}
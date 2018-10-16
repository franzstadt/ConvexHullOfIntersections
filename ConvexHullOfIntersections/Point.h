#pragma once
#include <cstdlib>
#include <string>

namespace ConvexHull
{
	struct Point
	{
		double x, y;

		Point(double px = 0.0, double py = 0.0) : x(px), y(py) {}
		double distance(const Point& p2)  const;
		static bool Equals(double a, double b);
		bool operator==(const Point& rhs) const;
		bool operator <(const Point& rhs) const 
		{
			return x < rhs.x || (Equals(x, rhs.x) && y < rhs.y);
		}
	};
}

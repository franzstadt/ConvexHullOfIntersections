#pragma once
#include <cstdlib>
#include <string>

namespace ConvexHull
{
	struct Point
	{
		double x, y;

		Point() : Point(0,0) {}
		Point(double px, double py) : x(px), y(py) {}
		double distance(const Point& p2)  const;
		static bool Equals(double a, double b);
		bool operator==(const Point& rhs) const;
		bool operator <(const Point& rhs) const;
	};
}


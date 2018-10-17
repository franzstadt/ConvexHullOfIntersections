#pragma once

namespace ConvexHull
{
	struct Point
	{
		double x, y;

		Point() : Point(0,0) {}
		Point(double px, double py) : x(px), y(py) {}
		double distance(const Point& p2)  const;
		bool operator==(const Point& rhs) const;
		bool operator <(const Point& rhs) const;
	};
}


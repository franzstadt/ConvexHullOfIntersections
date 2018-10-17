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

		// 2D cross product of xa and xb vectors, i.e. z-component of their 3D cross product.
		// Returns a positive value, if xab makes a counter-clockwise turn,
		// negative for clockwise turn, and zero if the points are collinear.
		static double Cross(const Point &x, const Point &a, const Point &b);
	};
}


#pragma once

#include "Point.h"
#include "Line.h"
#include <vector>

namespace ConvexHull
{
	class Circle
	{
		Point center;
		double r;
	public:
		Circle(double x, double y, double r) : center(x, y), r(r) {}
		std::vector<Point> GetCircleCircleIntersectionPoints(const Circle& c) const;
		std::vector<Point> GetCircleLineIntersectionPoints(const Line& l) const;
		bool operator==(const Circle& rhs) const;
	};
}
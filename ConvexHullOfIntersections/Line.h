#pragma once
#include "Point.h"

namespace ConvexHull
{
	struct Line
	{
		Point p1, p2;

		Line(const Point& point1, const Point& point2) : p1(point1), p2(point2) {}
		bool GetLineLineIntersectionPoint(const Line& l2, Point& intersection) const;
		
		bool operator==(const Line& rhs) const;
		inline bool OnLine(const Point& c) const;
	};
}


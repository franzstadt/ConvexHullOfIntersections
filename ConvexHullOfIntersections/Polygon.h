#pragma once
#include "Point.h"
#include "Constants.h"
#include <vector>
#include <stack>
#include <algorithm>

namespace ConvexHull
{
	static Point p_min;

	class Polygon
	{
	private:
		struct CompareToGetOrientation
		{
			Orientation GetOrientation(const Point& p, const Point& a, const Point& b) const
			{
				double val = (a.y - p.y) * (b.x - a.x) - (a.x - p.x) * (b.y - a.y);

				if (Point::Equals(0.0, val))
					return colinear;

				return (val > 0.0) ? clockwise : counterclockwise;
			}

			bool operator()(const Point& a, const Point& b) const
			{
				Orientation orientation = GetOrientation(p_min, a, b);

				if (orientation == colinear)
				{
					return p_min.distance(b) >= p_min.distance(a);
				}

				return orientation == counterclockwise;
			}
		} points_compare;
		std::vector<Point> m_points;

		Point Get2ndTop(std::stack<Point> &s) const;

		int GetLowest_y_Index(const std::vector<Point>& p) const;
		std::deque<Point> RemoveDuplicatedAngle(const Point& min) const;

	public:
		Polygon(const std::vector<Point>& p) : m_points(p) {}
		std::stack<Point> GetConvexHull();
		double GetConvexHullArea(const std::vector<Point>& hull) const;
	};
}
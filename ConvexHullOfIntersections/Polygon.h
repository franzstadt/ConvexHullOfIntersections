#pragma once
#include "Point.h"
#include "Constants.h"
#include <vector>
#include <algorithm>

namespace ConvexHull
{
	class Polygon
	{
	private:
		std::vector<Point> m_points;
		
		double Cross(const Point &O, const Point &A, const Point &B) const;

	public:
		Polygon(const std::vector<Point>& p) : m_points(p) {}
		std::vector<Point> GetConvexHull();
		double GetConvexHullArea(const std::vector<Point>& hull) const;
	};
}
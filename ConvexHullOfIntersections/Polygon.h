#pragma once
#include "Point.h"
#include "Constants.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

namespace ConvexHull
{
	class Polygon
	{
	private:
		std::set<Point> m_points;

		double Cross(const Point &O, const Point &A, const Point &B);

	public:
		Polygon(const std::set<Point>& p) : m_points(p) {}
		std::unordered_set<Point> GetConvexHull();
		double GetConvexHullArea( std::unordered_set< Point>& hull) const;
	};
}
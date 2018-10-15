#pragma once
#include "Point.h"
#include "Constants.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace ConvexHull
{
	class Polygon
	{
	private:
		std::set<Point> m_points;
		
		double Cross(const Point &O, const Point &A, const Point &B);

	public:
		std::vector<Point> convex_hull2(std::vector<Point> P);
		Polygon(const std::set<Point>& p) : m_points(p) {}
		std::unordered_map<int, Point> GetConvexHull();
		double GetConvexHullArea(const std::unordered_map<int, Point>& hull) const;
	};
}
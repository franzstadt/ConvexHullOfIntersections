#pragma once
#include "Point.h"
#include "Constants.h"

#include <vector>

namespace ConvexHull
{
	class PointCloud
	{
	public:
		PointCloud(const std::vector<Point>& p) : m_points(p) {}
		//Monotone chain convex hull algorithm
		std::vector<Point> GetConvexHull();
		double GetConvexHullArea(const std::vector<Point>& hull) const;

	private:
		std::vector<Point> m_points;
	};
}
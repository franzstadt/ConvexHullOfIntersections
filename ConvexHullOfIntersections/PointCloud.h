#pragma once
#include "Point.h"
#include "Constants.h"

#include <vector>

namespace ConvexHull
{
	class PointCloud
	{
	private:
		std::vector<Point> m_points;

		// 2D cross product of xa and xb vectors, i.e. z-component of their 3D cross product.
		// Returns a positive value, if xab makes a counter-clockwise turn,
		// negative for clockwise turn, and zero if the points are collinear.
		double Cross(const Point &x, const Point &a, const Point &b) const;

	public:
		PointCloud(const std::vector<Point>& p) : m_points(p) {}
		//Monotone chain convex hull algorithm
		std::vector<Point> GetConvexHull();
		double GetConvexHullArea(const std::vector<Point>& hull) const;
	};
}
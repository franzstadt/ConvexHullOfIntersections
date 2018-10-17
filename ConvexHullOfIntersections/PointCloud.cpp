#include "PointCloud.h"

#include <algorithm>

namespace ConvexHull
{
	double PointCloud::Cross(const Point &x, const Point &a, const Point &b) const
	{
		return (a.x - x.x) * (b.y - x.y) - (a.y - x.y) * (b.x - x.x);
	}

	std::vector<Point> PointCloud::GetConvexHull()
	{
		size_t n = m_points.size(), k = 0;

		if (n <= 3) 
			return m_points;
		
		std::vector<Point> convex_hull(2 * n);

		std::sort(m_points.begin(), m_points.end());

		for (size_t i = 0; i < n; ++i) 
		{
			while (k >= 2 && Cross(convex_hull[k - 2], convex_hull[k - 1], m_points[i]) <= 0)
			{
				k--;
			}
			convex_hull[k++] = m_points[i];
		}

		for (size_t i = n - 1, t = k + 1; i > 0; --i) 
		{
			while (k >= t && Cross(convex_hull[k - 2], convex_hull[k - 1], m_points[i - 1]) <= 0) 
			{
				k--; 
			}
			convex_hull[k++] = m_points[i - 1];
		}

		convex_hull.resize(k - 1);
		return convex_hull;
	}

	double PointCloud::GetConvexHullArea(const std::vector<Point>& convex_hull) const
	{
		double area = 0.0;
		size_t j = convex_hull.size() - 1;

		for (size_t i = 0; i < convex_hull.size(); ++i)
		{
			area += (convex_hull[j].x + convex_hull[i].x) * (convex_hull[j].y - convex_hull[i].y);
			j = i;
		}
		return abs(area / 2.0);
	}
}
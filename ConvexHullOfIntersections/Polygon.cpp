#include "Polygon.h"
#include <iterator>
#include <unordered_map>

namespace ConvexHull
{
	double Polygon::Cross(const Point &O, const Point &A, const Point &B) const
	{
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	}

	std::vector<Point> Polygon::GetConvexHull()
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

	double Polygon::GetConvexHullArea(const std::vector<Point>& hull) const
	{
		double area = 0.0;
		size_t j = hull.size() - 1;

		for (unsigned i = 0; i < hull.size(); i++)
		{
			area += (hull[j].x + hull[i].x) * (hull[j].y - hull[i].y);
			j = i;
		}
		return abs(area / 2.0);
	}
}
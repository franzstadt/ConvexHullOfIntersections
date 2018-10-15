#include "Polygon.h"

namespace ConvexHull
{
	double Polygon::Cross(const Point &O, const Point &A, const Point &B)
	{
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	}

	std::unordered_set<Point> Polygon::GetConvexHull()
	{
		size_t n = m_points.size(), k = 0, i = 0;
		std::unordered_set<Point> convex_hull;
		if (n <= 3)
		{
			for (const auto& p : m_points)
			{
				convex_hull.insert(p);
			}
		}

		for (const auto& point:m_points) 
		{
			while (k >= 2 && Cross(convex_hull[k - 2], convex_hull[k - 1], point) <= 0)
			{ 
				k--; 
			}
			convex_hull[k++] = point;
			i++;
		}

		size_t t = k + 1;
		Point prev;
		for (auto it = m_points.rbegin();it!=m_points.rend();++it) 
		{
			
			while (k >= t && Cross(convex_hull[k - 2], convex_hull[k - 1], prev) <= 0)
			{
				k--;
			}
			convex_hull[k++] = prev;
			prev = *it;
		}

		return convex_hull;
	}

	double Polygon::GetConvexHullArea( std::unordered_set<Point>& hull) const
	{
		double area = 0.0;
		int j = hull.size() - 1;

		for (unsigned i = 0; i < hull.size(); i++)
		{
			//area += (hull[j].x + hull[i].x) * (hull[j].y - hull[i].y);
			j = i;
		}
		return abs(area / 2.0);
	}
}
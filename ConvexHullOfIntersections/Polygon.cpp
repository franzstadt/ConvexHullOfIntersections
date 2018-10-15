#include "Polygon.h"
#include <iterator>
#include <unordered_map>

namespace ConvexHull
{
	double Polygon::Cross(const Point &O, const Point &A, const Point &B)
	{
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	}

	std::unordered_map<int, Point> Polygon::GetConvexHull()
	{
		size_t n = m_points.size();
		std::unordered_map<int, Point> convex_hull;
		int k = 0;

		if (n <= 3)
		{
			for (const auto& p : m_points)
			{
				convex_hull[k++] = p;
			}
			return convex_hull;
		}
		
		for (auto it = m_points.begin();it != m_points.end();++it) 
		{
			while (k >= 2 && Cross(convex_hull[k-2], convex_hull[k-1], *it) <= 0)
			{ 
				k--;
			}
			convex_hull[k++] = *it;
		}
		
		size_t t = k + 1;
		for (auto it = m_points.rbegin();std::next(it,1)!=m_points.rend();++it) 
		{
			while (k >= t && Cross(convex_hull[k - 2], convex_hull[k - 1], *std::next(it,1)) <= 0)
			{
				k--;
			}
			convex_hull[k++] = *std::next(it,1);
		}

		convex_hull.erase(k-1);
		return convex_hull;
	}

	std::vector<Point> Polygon::convex_hull2(std::vector<Point> P)
	{
		using namespace std;
		size_t n = P.size(), k = 0;
		if (n <= 3) return P;
		vector<Point> H(2 * n);

		// Sort points lexicographically
		sort(P.begin(), P.end());

		// Build lower hull
		for (size_t i = 0; i < n; ++i) {
			while (k >= 2 && Cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
			H[k++] = P[i];
		}

		// Build upper hull
		for (size_t i = n - 1, t = k + 1; i > 0; --i) {
			while (k >= t && Cross(H[k - 2], H[k - 1], P[i - 1]) <= 0) k--;
			H[k++] = P[i - 1];
		}

		H.resize(k - 1);
		return H;
	}

	double Polygon::GetConvexHullArea(const std::unordered_map<int,Point>& hull) const
	{
		double area = 0.0;
		int j = hull.size() - 1;

		for (unsigned i = 0; i < hull.size(); i++)
		{
			area += (hull.find(j)->second.x + hull.find(i)->second.x) * (hull.find(j)->second.y - hull.find(i)->second.y);
			j = i;
		}
		return abs(area / 2.0);
	}
}
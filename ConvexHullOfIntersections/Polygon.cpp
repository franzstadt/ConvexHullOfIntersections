#include "Polygon.h"

namespace ConvexHull
{
	Point Polygon::Get2ndTop(std::stack<Point>& s) const
	{
		if (s.size() < 2)
			throw std::runtime_error("get2ndtop: stack size < 2"); // TODO: refactor
		Point temp = s.top();
		s.pop();

		Point second_top = s.top();
		s.push(temp);
		return second_top;
	}

	int Polygon::GetLowest_y_Index(const std::vector<Point>& p) const
	{
		if (m_points.empty())
			throw std::runtime_error("get_lowest_y_index: points empty"); // TODO: refactor
		double min_y = m_points[0].y;
		int min_index = 0;
		for (unsigned i = 1; i < p.size(); i++)
		{
			if ((p[i].y < min_y) || (min_y == p[i].y && p[i].x < p[min_index].x))
				min_y = p[i].y, min_index = i;
		}
		return min_index;

	}

	std::deque<Point> Polygon::RemoveDuplicatedAngle(const Point& min) const
	{
		std::deque<Point> removed_duplicated;
		for (unsigned i = 1; i < m_points.size(); i++)
		{
			while (i < m_points.size() - 1 && points_compare.GetOrientation(min, m_points[i], m_points[i + 1]) == colinear)
				i++;

			removed_duplicated.push_back(m_points[i]);
		}
		return removed_duplicated;
	}

	std::stack<Point> Polygon::GetConvexHull()
	{
		std::stack<Point> convex_points;
		if (m_points.size() < 2)
			return convex_points;

		int min_index = GetLowest_y_Index(m_points);
		std::swap(m_points[0], m_points[min_index]);
		p_min = m_points[0];
		std::sort(m_points.begin() + 1, m_points.end(), CompareToGetOrientation());

		int m = 1;
		std::deque<Point> points_without_duplicated_angle = RemoveDuplicatedAngle(p_min);
		points_without_duplicated_angle.push_front(m_points[0]);


		if (points_without_duplicated_angle.size() < 3) 
			return convex_points;

		convex_points.push(points_without_duplicated_angle[0]);
		convex_points.push(points_without_duplicated_angle[1]);
		convex_points.push(points_without_duplicated_angle[2]);

		for (unsigned i = 3; i < points_without_duplicated_angle.size(); i++)
		{
			while (convex_points.size() > 1 && points_compare.GetOrientation(Get2ndTop(convex_points), convex_points.top(), points_without_duplicated_angle[i]) != counterclockwise)
				convex_points.pop();

			convex_points.push(points_without_duplicated_angle[i]);
		}
		return convex_points;
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
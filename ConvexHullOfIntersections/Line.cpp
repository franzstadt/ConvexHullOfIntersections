#include "Line.h"
#include "Constants.h"
#include <algorithm>

namespace ConvexHull
{
	bool Line::GetLineLineIntersectionPoints(const Line & l2, Point & intersection) const
	{
		double dx = p2.x - p1.x;
		double dy = p2.y - p1.y;

		double m1 = dy / dx;

		double c1 = p1.y - m1 * p1.x;

		dx = l2.p2.x - l2.p1.x;
		dy = l2.p2.y - l2.p1.y;

		double m2 = dy / dx;
		double c2 = l2.p1.y - m2 * l2.p1.x;

		if (Point::Equals((m1 - m2),0.0))
			return false;
		else
		{
			intersection.x = round((c2 - c1) / (m1 - m2)*10000.0) / 10000.0;
			intersection.y = round((m1 * intersection.x + c1)*10000.0) / 10000.0;

			if (OnLine(intersection) && l2.OnLine(intersection))
				return true;
			else
				return false;
		}
	}

	inline bool Line::OnLine(const Point & c) const
	{
		return c.x <= std::max(p1.x, p2.x) && c.x >= std::min(p1.x, p2.x) && c.y <= std::max(p1.y, p2.y) && c.y >= std::min(p1.y, p2.y); // TODO: Review
	}

	bool Line::operator==(const Line& rhs) const
	{
		return p1 == rhs.p1 && p2 == rhs.p2;
	}
}
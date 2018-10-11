#include "Line.h"
#include "Constants.h"
#include <algorithm>
#include "Helper.h"

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
			intersection.x = round_4_decimal((c2 - c1) / (m1 - m2));
			intersection.y = round_4_decimal(m1 * intersection.x + c1);

			if (OnLine(intersection) && l2.OnLine(intersection))
				return true;
			else
				return false;
		}
	}

	inline double Det(double a, double b, double c, double d)
	{
		return a * d - b * c;
	}

	bool Line::GetLineLineIntersectionPoints2(const Line & l2, Point & intersection) const
	{
		double detL1 = Det(p1.x, p1.y, p2.x, p2.y);
		double detL2 = Det(l2.p1.x, l2.p1.y, l2.p2.x, l2.p2.y);
		double x1mx2 = p1.x - p2.x;
		double x3mx4 = l2.p1.x - l2.p2.x;
		double y1my2 = p1.y - p2.y;
		double y3my4 = l2.p1.y - l2.p2.y;

		double xnom = Det(detL1, x1mx2, detL2, x3mx4);
		double ynom = Det(detL1, y1my2, detL2, y3my4);
		double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
		if (Point::Equals(denom, 0.0))
			return false;

		intersection.x = round_4_decimal(xnom / denom);
		intersection.y = round_4_decimal(ynom / denom);

		if (!isfinite(intersection.x) || !isfinite(intersection.y)) 
			return false;

		return true; 
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
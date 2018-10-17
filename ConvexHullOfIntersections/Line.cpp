#include "Line.h"
#include "Constants.h"
#include "Helper.h"

#include <algorithm>

namespace ConvexHull
{
	bool Line::GetLineLineIntersectionPoint(const Line & l2, Point & intersection) const
	{
		double determinant_l1 = Determinant(p1.x, p1.y, p2.x, p2.y);
		double determinant_l2 = Determinant(l2.p1.x, l2.p1.y, l2.p2.x, l2.p2.y);

		double x1_minus_x2 = p1.x - p2.x;
		double x3_minus_x4 = l2.p1.x - l2.p2.x;

		double y1_minus_y2 = p1.y - p2.y;
		double y3_minus_y4 = l2.p1.y - l2.p2.y;

		double x_numerator = Determinant(determinant_l1, x1_minus_x2, determinant_l2, x3_minus_x4);
		double y_numerator = Determinant(determinant_l1, y1_minus_y2, determinant_l2, y3_minus_y4);

		double common_denominator = Determinant(x1_minus_x2, y1_minus_y2, x3_minus_x4, y3_minus_y4);

		if (Equals(common_denominator, 0.0))
			return false;

		intersection.x = x_numerator / common_denominator;//round_4_decimal(x_numerator / common_denominator);
		intersection.y = y_numerator / common_denominator;//round_4_decimal(y_numerator / common_denominator);

		if (!isfinite(intersection.x) || !isfinite(intersection.y) || !OnLine(intersection) || !l2.OnLine(intersection))
			return false;

		return true;
	}

	inline bool Line::OnLine(const Point & c) const
	{
		return islessequal(c.x, std::max(p1.x, p2.x)) && isgreaterequal(c.x, std::min(p1.x, p2.x)) && islessequal(c.y, std::max(p1.y, p2.y)) && isgreaterequal(c.y, std::min(p1.y, p2.y));
	}

	bool Line::operator==(const Line& rhs) const
	{
		return p1 == rhs.p1 && p2 == rhs.p2;
	}
}
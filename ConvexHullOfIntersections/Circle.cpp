#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include "Helper.h"

namespace ConvexHull
{
	std::vector<Point> Circle::GetCircleCircleIntersectionPoints(const Circle& c) const
	{
		std::vector<Point> intersection_points;

		double d = center.distance(c.center);
		if ((d > r + c.r) || d < abs(r - c.r))
			return intersection_points;

		double r_squared = r * r;
		double cr_squared = c.r * c.r;

		double r1s_minus_r2s_squared = ((r_squared) - (cr_squared))*((r_squared) - (cr_squared));
		double r1s_plus_r2s = (r_squared) + (cr_squared);
		double r1s_minus_r2s = (r_squared) - (cr_squared);
		double x1_x2_squared = (center.x*center.x) - (c.center.x*c.center.x);
		double y1_y2_squared = (center.y*center.y) - (c.center.y*c.center.y);
		double x2_m_x1 = (c.center.x - center.x);
		double x1_p_x2 = (center.x + c.center.x);
		double y1_p_y2 = (center.y + c.center.y);
		double y2_m_y1 = (c.center.y - center.y);

		double d_squared = d * d;

		double det = ((2.0 * r1s_plus_r2s) / (d*d)) - ((r1s_minus_r2s_squared) / (d_squared*d_squared)) - 1.0;
		double D = det < 0.0 ? 0.0 : sqrt(det) / 2.0;

		double x1 = (x1_p_x2 / 2.0) + (r1s_minus_r2s / (2.0 * d_squared))*x2_m_x1 + (D*y2_m_y1);
		double x2 = (x1_p_x2 / 2.0) + (r1s_minus_r2s / (2.0 * d_squared))*x2_m_x1 - (D*y2_m_y1);
		double y1 = (y1_p_y2 / 2.0) + (r1s_minus_r2s / (2.0 * d_squared))*y2_m_y1 - (D*x2_m_x1);
		double y2 = (y1_p_y2 / 2.0) + (r1s_minus_r2s / (2.0 * d_squared))*y2_m_y1 + (D*x2_m_x1);

		intersection_points.push_back(Point(x1, y1));

		if (Equals(d, abs(r - c.r)) || Equals(d, (r + c.r)))
			return intersection_points;

		intersection_points.push_back(Point(x2, y2));
		return intersection_points;
	}


	std::vector<Point> Circle::GetCircleLineIntersectionPoints(const Line & l) const
	{
		std::vector<Point> intersection_points;

		double x1 = l.p1.x - center.x;
		double x2 = l.p2.x - center.x;

		double y1 = l.p1.y - center.y;
		double y2 = l.p2.y - center.y;

		double dx = x2 - x1;
		double dy = y2 - y1;

		double sign_dy = dy < 0.0 ? -1.0 : 1.0; 

		double dr_pow_2 = dx * dx + dy * dy;

		double common_determinant = Determinant(x1, x2, y1, y2);

		double discriminant = r * r*dr_pow_2 - common_determinant * common_determinant;
		double sqrt_disc = std::sqrt(discriminant);

		if (discriminant < 0.0)
			return intersection_points;

		double intersection_x1 = (common_determinant*dy + sign_dy * dx*sqrt_disc) / dr_pow_2;
		double intersection_y1 = (-common_determinant * dx + abs(dy) *sqrt_disc) / dr_pow_2;
		
		Point p1(intersection_x1 + center.x, intersection_y1 + center.y);
		if (l.OnLine(p1))
			intersection_points.push_back(p1);

		if (Equals(discriminant, 0.0))
			return intersection_points;

		double intersection_x2 = (common_determinant*dy - sign_dy * dx*sqrt_disc) / dr_pow_2;
		double intersection_y2 = (-common_determinant * dx - abs(dy) *sqrt_disc) / dr_pow_2;

		Point p2(intersection_x2 + center.x, intersection_y2 + center.y);
		if (l.OnLine(p2))
			intersection_points.push_back(p2);

		return intersection_points;
	}

	bool Circle::operator==(const Circle& rhs) const
	{
		return center == rhs.center && Equals(r ,rhs.r);
	}
}
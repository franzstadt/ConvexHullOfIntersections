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

		double r1s_minus_r2s_squared = ((r*r) - (c.r*c.r))*((r*r) - (c.r*c.r));
		double r1s_plus_r2s = (r*r) + (c.r*c.r);
		double r1s_minus_r2s = (r*r) - (c.r*c.r);
		double x1_x2_squared = (center.x*center.x) - (c.center.x*c.center.x);
		double y1_y2_squared = (center.y*center.y) - (c.center.y*c.center.y);
		double x2_m_x1 = (c.center.x - center.x);
		double x1_p_x2 = (center.x + c.center.x);
		double y1_p_y2 = (center.y + c.center.y);
		double y2_m_y1 = (c.center.y - center.y);

		double det = ((2 * r1s_plus_r2s) / (d*d)) - ((r1s_minus_r2s_squared) / (d*d*d*d)) - 1;
		double D = det < 0 ? 0 : sqrt(det) / 2;

		double x1 = (x1_p_x2 / 2) + (r1s_minus_r2s / (2 * d*d))*x2_m_x1 + (D*y2_m_y1);
		double x2 = (x1_p_x2 / 2) + (r1s_minus_r2s / (2 * d*d))*x2_m_x1 - (D*y2_m_y1);
		double y1 = (y1_p_y2 / 2) + (r1s_minus_r2s / (2 * d*d))*y2_m_y1 - (D*x2_m_x1);
		double y2 = (y1_p_y2 / 2) + (r1s_minus_r2s / (2 * d*d))*y2_m_y1 + (D*x2_m_x1);

		intersection_points.push_back(Point(x1, y1));

		if (d == abs(r - c.r) || d == (r + c.r))
			return intersection_points;

		intersection_points.push_back(Point(x2, y2));
		return intersection_points;
	}

	std::vector<Point> Circle::GetCircleCircleIntersectionPoints2(const Circle& c) const
	{
		std::vector<Point> intersection_points;
		
		//x'=[(x-u)*cos(alfa)-(y-v)*sin(Alfa)]+u
		//y'=[(x-u)*sin(alfa)-(y-v)*cos(Alfa)]+v
		double d = center.distance(c.center);

		double R_pow_2 = pow(r, 2);
		double r_pow_2 = pow(c.r, 2);
		
		double x = (pow(d, 2) - r_pow_2 + R_pow_2) / (2*d);
		double y = sqrt(R_pow_2 - pow(x, 2));

		
		intersection_points.push_back(Point(round_4_decimal(x), round_4_decimal(y)));

		if (d == abs(r - c.r) || d == (r + c.r))
			return intersection_points;

		intersection_points.push_back(Point(round_4_decimal (-x), round_4_decimal( -y)));
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

		double dr_pow_2 = pow(dx, 2) + pow(dy, 2);

		double common_determinant = Determinant(x1, x2, y1, y2);

		double discriminant = pow(r, 2)*dr_pow_2 - pow(common_determinant, 2);
		double sqrt_disc = sqrt(discriminant);

		if (discriminant < 0)
			return intersection_points;

		double intersection_x1 = (common_determinant*dy + sign_dy * dx*sqrt_disc) / dr_pow_2;
		double intersection_y1 = (-common_determinant * dx + abs(dy) *sqrt_disc) / dr_pow_2;
		
		Point p1(intersection_x1 + center.x, intersection_y1 + center.y);
		if (l.OnLine(p1))
			intersection_points.push_back(p1);

		if (Point::Equals(discriminant, 0.0))
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
		return center == rhs.center && Point::Equals(r ,rhs.r);
	}
}
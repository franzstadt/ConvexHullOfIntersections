#include "Circle.h"
#include "Point.h"
#include "Line.h"

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

	std::vector<Point> Circle::GetCircleLineIntersectionPoints(const Line & l) const
	{
		std::vector<Point> intersection_points;

		double dx = l.p2.x - l.p1.x;
		double dy = l.p2.y - l.p1.y;
		double sign = dy < 0.0 ? -1.0 : 1.0;
		double signx = dx < 0.0 ? -1.0 : 1.0;
		double slope = dy / dx;
		double d = l.p1.y - (slope*l.p1.x);
		double d2 = l.p2.y - (slope*l.p2.x);
		double A = -(2.0 * center.x);
		double B = -(2.0 * center.y);
		double C = (center.x*center.x) + (center.y*center.y) - (r*r);

		double numertor_fix_part_for_x = (2.0 * slope*d) + A + (B*slope);
		double numertor_fix_part_for_y = (A*slope) - (2.0 * d) + (slope*slope*B);


		double disc_x = (numertor_fix_part_for_x*numertor_fix_part_for_x) - (4.0 * ((1.0 + (slope*slope))*((d*d) + (B*d) + C)));
		double disc_y = (numertor_fix_part_for_y*numertor_fix_part_for_y) - (4.0 * (1.0 + (slope*slope))*((d*d) - (A*slope*d) + (slope*slope*C)));

		if (disc_x < 0.0 || disc_y < 0.0)
			return intersection_points;

		double denominator = 2.0*(1.0 + (slope*slope));

		double x1 = (-numertor_fix_part_for_x + signx * sqrt(disc_x)) / denominator;
		double x2 = (-numertor_fix_part_for_x - signx * sqrt(disc_x)) / denominator;
		double y1 = (-numertor_fix_part_for_y + sign * sqrt(disc_y)) / denominator;
		double y2 = (-numertor_fix_part_for_y - sign * sqrt(disc_y)) / denominator;

		Point p1(x1, y1);
		if (l.OnLine(p1))
			intersection_points.push_back(p1);

		if (disc_x == 0 || disc_y == 0)
			return intersection_points;

		Point p2(x2, y2);
		if (l.OnLine(p2))
			intersection_points.push_back(p2);

		return intersection_points;
	}

	bool Circle::operator==(const Circle& rhs) const
	{
		return center == rhs.center && Point::Equals(r ,rhs.r);
	}
}
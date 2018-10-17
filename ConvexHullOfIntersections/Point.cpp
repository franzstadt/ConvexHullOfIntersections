#include "Point.h"
#include <cmath>
#include "Constants.h"
#include "Helper.h"

namespace ConvexHull
{
	double Point::distance(const Point& p2)  const
	{
		double dx = x - p2.x;
		double dy = y - p2.y;

		return std::sqrt(dx * dx + dy * dy);
	}

	bool Point::operator==(const Point& rhs) const
	{
		return Equals(x, rhs.x) && Equals(y, rhs.y);
	}

	//Compare Points lexicographically
	bool Point::operator<(const Point & rhs) const
	{
		return x < rhs.x || (Equals(x, rhs.x) && y < rhs.y);
	}

	double Point::Cross(const Point &x, const Point &a, const Point &b)
	{
		return (a.x - x.x) * (b.y - x.y) - (a.y - x.y) * (b.x - x.x);
	}
}
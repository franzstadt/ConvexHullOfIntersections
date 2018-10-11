#include "Point.h"
#include <cmath>
#include "Constants.h"

namespace ConvexHull
{
	double Point::distance(const Point& p2)  const
	{
		return sqrt(((x - p2.x)*(x - p2.x)) + ((y - p2.y)*(y - p2.y)));
	}

	bool Point::Equals(double a, double b)
	{
		return std::fabs(a - b) < kEpsilon;
	}

	bool Point::operator==(const Point& rhs) const
	{
		return Equals(x, rhs.x) && Equals(y, rhs.y);
	}
}
#include "Point.h"
#include <math.h>
#include "Constants.h"

namespace ConvexHull
{
	double Point::distance(const Point& p2)  const
	{
		return sqrt(((x - p2.x)*(x - p2.x)) + ((y - p2.y)*(y - p2.y)));
	}

	bool Point::Equals(double a, double b, double epsilon)
	{
		return std::abs(a - b) < epsilon;
	}

	bool Point::operator==(const Point& rhs) const
	{
		return Equals(x, rhs.x) && Equals(y, rhs.y);
	}
}
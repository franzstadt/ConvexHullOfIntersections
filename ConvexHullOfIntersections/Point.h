#pragma once
#include <cstdlib>
#include <string>

namespace ConvexHull
{
	struct Point
	{
		double x, y;

		Point(double px = 0.0, double py = 0.0) : x(px), y(py) {}
		double distance(const Point& p2)  const;
		static bool Equals(double a, double b);
		bool operator==(const Point& rhs) const;
		bool operator <(const Point &p) const 
		{
			return x < p.x || (Equals(x, p.x) && y < p.y);
		}
	};
}

namespace std
{
	template<>
	struct hash<ConvexHull::Point>
	{
		size_t
			operator()(const ConvexHull::Point & obj) const
		{
			return hash<string>()(to_string(obj.x)+"_"+to_string(obj.y));
		}
	};
}
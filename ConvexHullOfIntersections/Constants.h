#pragma once

namespace ConvexHull
{
	enum Orientation { colinear = 0, clockwise = 1, counterclockwise = 2 };
	const double kEpsilon = 0.0001;
}
#pragma once
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "PointCloud.h"

#include <fstream>

namespace ConvexHull
{
	class Solution
	{
	private:
		std::string m_input_file_name;

		bool m_input_loaded;
		bool m_intersection_points_calculated;
		int shapes_count;

		std::vector<Circle> circles;
		std::vector<Line> lines;
		std::vector<Point> points;
		std::vector<Point> convex_hull_points;
		void ReadStream(std::istream& input);

	public:
		Solution(std::string input_file_name = "");
		void ReadInput();
		void GetIntersectionPoints();
		void CalculateConvexHull();
	
	};

}
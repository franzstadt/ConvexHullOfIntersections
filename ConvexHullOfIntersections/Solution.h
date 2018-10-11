#pragma once
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Polygon.h"
#include <fstream>
namespace ConvexHull
{
	class Solution
	{
	public:
		Solution(std::string input_file_name = "", std::string check_file_inters = "", std::string check_file_convhull = "");
		void GetIntersectionPoints();
		void CalculateConvexHull();
		~Solution();
	private:
		int shapes_count;
		std::vector<Circle> circles;
		std::vector<Line> lines;
		std::vector<Point> points;
		std::vector<Point> expected_points;
		std::vector<Point> expected_convex_points;
		std::ifstream input;
		std::ifstream expected_input;
		std::ifstream expected_hull_input;
		std::string sline;
		std::stack<Point> convex_hull_points;
		std::vector<Point> not_found_convex;
		std::vector<Point> area;
		void CheckIntersectionPoints();
		void CheckConvexHullPoints();
		void ReadFromCin();
	};

}
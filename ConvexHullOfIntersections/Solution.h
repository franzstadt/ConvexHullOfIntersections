#pragma once
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Polygon.h"
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
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
		std::set<Point> points;
		std::vector<Point> expected_points;
		std::unordered_set<Point> expected_convex_points;
		std::ifstream input;
		std::ifstream expected_input;
		std::ifstream expected_hull_input;
		std::string sline;
		std::unordered_map<int,Point> convex_hull_points;
		std::vector<Point> not_found_convex;
		std::vector<Point> area;
		void CheckIntersectionPoints();
		void CheckConvexHullPoints();
		void ReadFromCin();
	};

}
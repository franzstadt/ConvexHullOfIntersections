#include "Solution.h"
#include "Helper.h"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <set>

namespace ConvexHull
{
	Solution::Solution(std::string input_file_name) :
		m_input_file_name(input_file_name), m_input_loaded(false), m_intersection_points_calculated(false) {}

	void Solution::ReadStream(std::istream& input)
	{
		if(!(input >> shapes_count))
			throw std::runtime_error("Invalid shape count.");

		if (shapes_count > 0 && shapes_count <= 1000)
		{
			std::string line;
			std::getline(input, line);
			for (int i = 0; i < shapes_count; ++i)
			{
				std::getline(input, line);
				std::stringstream linestream(line);
				char type_of_shape;
				if(!(linestream >> type_of_shape))
					throw std::runtime_error("Invalid shape type.");

				switch (type_of_shape)
				{
					case 'C':
					{
						double x, y, radius;

						if (linestream >> x >> y >> radius)
						{
							Circle c(x, y, radius);
							circles.push_back(c);
						}
						else
							throw std::runtime_error("Invalid circle.");

						break;
					}
					case 'L':
					{
						double x1, y1, x2, y2;

						if(linestream >> x1 >> y1 >> x2 >> y2)
						{ 
							Point a(x1, y1), b(x2, y2);
							Line l(a, b);
							lines.push_back(l);
						}
						else
							throw std::runtime_error("Invalid circle.");

						break;
					}
					default: throw std::runtime_error("Bad shape type.");
				}
			}
			m_input_loaded = true;
		}
		else
			throw std::runtime_error("The number of shapes must be between 0 and 1000.");
	}

	void Solution::GetIntersectionPoints()
	{
		if (!m_input_loaded)
		{
			std::cout << "Input is not loaded." << std::endl;
			return;
		}

		for (size_t i = 0; i < lines.size(); ++i)
		{
			if (i + 1 >= lines.size())
				continue;

			for (size_t j = i + 1; j < lines.size(); ++j)
			{
				Point new_point;
				if (lines[i].GetLineLineIntersectionPoint(lines[j], new_point))
				{
					points.push_back(new_point);
				}
			}

		}
		for (size_t i = 0; i < circles.size(); ++i)
		{
			if (i + 1 >= circles.size())
				continue;

			for (size_t j = i + 1; j < circles.size(); ++j)
			{
				std::vector<Point> new_points = circles[i].GetCircleCircleIntersectionPoints(circles[j]);
				if (new_points.size() > 0)
				{
					points.insert(points.end(), new_points.begin(), new_points.end());				
				}
			}

		}
		for (const auto& circle : circles)
		{
			for (const auto& line : lines)
			{
				std::vector<Point> new_points = circle.GetCircleLineIntersectionPoints(line);
				if (new_points.size() > 0)
				{
					points.insert(points.end(), new_points.begin(), new_points.end());
				}
			}
		}

		std::cout << points.size() << std::endl;
		std::cout << std::fixed;
		std::cout << std::setprecision(4);
		for (const auto& point : points)
		{
			std::cout << round_4_decimal(point.x) << " " << round_4_decimal(point.y) << std::endl;
		}
		if(!points.empty())
			m_intersection_points_calculated = true;
	}

	void Solution::CalculateConvexHull() 
	{
		if (!m_intersection_points_calculated)
		{
			std::cout << "Intersection points are not calculated." << std::endl;
			return;
		}

		PointCloud p(points);

		convex_hull_points = p.GetConvexHull();
		std::cout << convex_hull_points.size() << std::endl;
		for (const auto& point : convex_hull_points)
		{
			std::cout << round_4_decimal(point.x) << " " << round_4_decimal(point.y) << std::endl;
		}
		std::cout << round_4_decimal(p.GetConvexHullArea(convex_hull_points)) << std::endl;
	}

	void Solution::ReadInput()
	{
		std::ifstream input;
		std::ifstream expected_input;
		std::ifstream expected_hull_input;

		if (!m_input_file_name.empty())
		{
			input.open(m_input_file_name);
			if (!input)
				throw std::runtime_error("Input file cannot be opened.");
		
			ReadStream(input);
		}
		else
		{
			ReadStream(std::cin);
		}
		
	}
}
#include "Solution.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Helper.h"

namespace ConvexHull
{
	Solution::Solution(std::string input_file_name, std::string check_file_inters, std::string check_file_convhull)
	{
		if (!input_file_name.empty())
		{
			input.open(input_file_name);
			if (!input)
				throw std::runtime_error("Bad input");
		}
		if (!check_file_inters.empty())
		{
			expected_input.open(check_file_inters);
			if (!expected_input)
				throw std::runtime_error("Bad input");
		}
		if (!check_file_convhull.empty())
		{
			expected_hull_input.open(check_file_convhull);
			if (!expected_hull_input)
				throw std::runtime_error("Bad input");
		}

		if (input_file_name.empty())
			ReadFromCin();
		else
		{
			input >> shapes_count;

			if (shapes_count > 0 && shapes_count <= 1000)
			{
				std::getline(input, sline);
				for (int i = 0; i < shapes_count; i++)
				{
					std::getline(input, sline);
					std::stringstream linestream(sline);
					char type_of_shape;
					linestream >> type_of_shape;

					switch (type_of_shape)
					{
					case 'C':
					{
						double x, y, radius;

						linestream >> x >> y >> radius;
						Circle c(x, y, radius);
						circles.push_back(c);
						break;
					}
					case 'L':
					{
						double x1, y1, x2, y2;

						linestream >> x1 >> y1 >> x2 >> y2;
						Point a(x1, y1), b(x2, y2);
						Line l(a, b);
						lines.push_back(l);
						break;
					}
					default: break;
					}
				}
			}
		}

		if (!check_file_inters.empty())
		{
			std::getline(expected_input, sline);
			for (int i = 0; i < 15; i++)
			{
				std::getline(expected_input, sline);
				std::stringstream linestream(sline);
				double x, y;
				linestream >> x >> y;
				Point p(x, y);
				expected_points.push_back(p);
			}
		}
		if (!check_file_convhull.empty())
		{
			std::getline(expected_hull_input, sline);
			for (int i = 0; i < 9; i++)
			{
				std::getline(expected_hull_input, sline);
				std::stringstream linestream(sline);
				double x, y;
				linestream >> x >> y;
				Point p(x, y);
				expected_convex_points.push_back(p);
			}
		}
	}

	void Solution::GetIntersectionPoints()
	{
		for (unsigned i = 0; i < lines.size(); i++)
		{
			if (i + 1 < lines.size())
				for (unsigned j = i + 1; j < lines.size(); j++)
				{
					Point new_point(0, 0);
					if (lines[i].GetLineLineIntersectionPoints(lines[j], new_point))
						points.push_back(new_point);
				}
		}
		for (unsigned i = 0; i < circles.size(); i++)
		{
			if (i + 1 < circles.size())
				for (unsigned j = i + 1; j < circles.size(); j++)
				{
					std::vector<Point> new_points = circles[i].GetCircleCircleIntersectionPoints(circles[j]);
					points.insert(points.end(), new_points.begin(), new_points.end());
				}
		}
		for (auto circle : circles)
			for (auto line : lines)
			{
				std::vector<Point> new_points = circle.GetCircleLineIntersectionPoints(line);
				points.insert(points.end(), new_points.begin(), new_points.end());
			}
		std::cout << points.size() << std::endl;
		CheckIntersectionPoints();
	}

	void Solution::CheckIntersectionPoints()
	{
		std::vector<Point> not_found;
		for (auto i : points)
		{
			Point tmp(round_4_decimal(i.x), round_4_decimal(i.y));
			std::cout << tmp.x << " " << tmp.y << std::endl;
			if (!expected_points.empty())
			{
				Point tmp(round(i.x * 10000) / 10000, round(i.y * 10000) / 10000);
				auto it = find(expected_points.begin(), expected_points.end(), tmp);
				if (it != expected_points.end())
					expected_points.erase(it);
				else
					not_found.push_back(tmp);
			}
		}
		if ((!expected_points.empty() || !not_found.empty()) && !points.empty())
		{
			std::cout << std::endl << "missed:" << std::endl;
			for (auto i : expected_points)
				std::cout << std::setprecision(5) << i.x << " " << i.y << std::endl;
			std::cout << "extra:" << std::endl;
			for (auto i : not_found)
				std::cout << std::setprecision(5) << i.x << " " << i.y << std::endl;
		}
	}

	void Solution::CheckConvexHullPoints() 
	{
		while (!convex_hull_points.empty())
		{
			Point i = convex_hull_points.top();
			Point tmp(round_4_decimal(i.x), round_4_decimal(i.y));
			std::cout << tmp.x << " " << tmp.y << std::endl;

			if (!expected_convex_points.empty())
			{
				auto it = find(expected_convex_points.begin(), expected_convex_points.end(), tmp);
				if (it != expected_convex_points.end())
				{
					area.push_back(tmp);
					expected_convex_points.erase(it);
				}
				else
					not_found_convex.push_back(tmp);
			}
			else
				area.push_back(tmp);

			convex_hull_points.pop();
		}
		if ((!expected_convex_points.empty() || !not_found_convex.empty()) && !convex_hull_points.empty())
		{
			std::cout << std::endl << "missed:" << std::endl;
			for (auto i : expected_convex_points)
				std::cout << std::setprecision(5) << i.x << " " << i.y << std::endl;
			std::cout << "extra:" << std::endl;
			for (auto i : not_found_convex)
				std::cout << std::setprecision(5) << i.x << " " << i.y << std::endl;
		}
	}

	void Solution::ReadFromCin()
	{
		std::cin >> shapes_count;

		if (shapes_count > 0 && shapes_count <= 1000)
		{
			std::getline(std::cin, sline);
			for (int i = 0; i < shapes_count; i++)
			{
				std::getline(std::cin, sline);
				std::stringstream linestream(sline);
				char type_of_shape;
				linestream >> type_of_shape;

				switch (type_of_shape)
				{
				case 'C':
				{
					double x, y, radius;

					linestream >> x >> y >> radius;
					Circle c(x, y, radius);
					circles.push_back(c);
					break;
				}
				case 'L':
				{
					double x1, y1, x2, y2;

					linestream >> x1 >> y1 >> x2 >> y2;
					Point a(x1, y1), b(x2, y2);
					Line l(a, b);
					lines.push_back(l);
					break;
				}
				default: break;
				}
			}
		}
	}

	void Solution::CalculateConvexHull() 
	{
		Polygon p(points);

		convex_hull_points = p.GetConvexHull();
		std::cout << convex_hull_points.size() << std::endl;
		CheckConvexHullPoints();
		std::cout << std::setprecision(9) << round_4_decimal(p.GetConvexHullArea(area)) << std::endl;
	}

	Solution::~Solution()
	{
		input.close();
		expected_hull_input.close();
		expected_input.close();
	}

	
}
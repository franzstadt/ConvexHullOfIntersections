#include "pch.h"
#include "Point.h"
#include "Point.cpp"
#include "Line.h"
#include "Line.cpp"
#include "Circle.h"
#include "Circle.cpp"
#include "PointCloud.h"
#include "PointCloud.cpp"
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

namespace ConvexHullUnitTest
{
	using namespace ConvexHull;
	using std::runtime_error;
	using std::vector;
	using std::ifstream;
	using std::string;
	using std::stringstream;
	using std::stack;
	using std::to_string;

	std::vector<Point> test_points;

	TEST(HelperFunctionsTest, EqualsTest)
	{
		const double d1 = M_PI;
		const double d2 = sin(double(M_PI)) + d1;
		EXPECT_TRUE(Equals(d1, d2));
	}
	TEST(PointTest, DistanceTest)
	{
		const Point p1(12, 5);
		const Point p2(12, 5);
		EXPECT_DOUBLE_EQ(p1.distance(p2), 0);

		const Point p3(12, 5);
		const Point p4(0, 5);
		EXPECT_DOUBLE_EQ(p3.distance(p4), 12);
		EXPECT_DOUBLE_EQ(p4.distance(p3), 12);

		const Point p5(12, 0);
		const Point p6(12, 5);
		EXPECT_DOUBLE_EQ(p6.distance(p5), 5);
		EXPECT_DOUBLE_EQ(p5.distance(p6), 5);
	}
	TEST(PointTest, EQTest)
	{
		const Point p1(12, 5);
		const Point p2(12, 5);
		EXPECT_EQ(p1, p2);

		const Point p3(0, 5);
		const Point p4(12, 5);
		EXPECT_FALSE(p3 == p4);
	}
	TEST(LineTest, EQTest)
	{
		const Point p1(12, 5);
		const Point p2(14, 6);
		Line l1(p1, p2);
		const Line l2(p1, p2);

		EXPECT_EQ(l1, l2);
		l1.p1.x--;
		EXPECT_FALSE(l1 == l2);
	}
	TEST(LineTest, IntersectionTest)
	{
		const Point p1(-2, 1);
		const Point p2(12, 6);
		const Line l1(p1, p2);
		const Point p3(-4, 9);
		const Point p4(8, -4);
		const Line l2(p3, p4);
		const Point p5(5, 2);
		const Point p6(7, 9);
		const Line l3(p5, p6);
		const Point p7(-3, -3);
		const Point p8(-1, 2);
		const Line l4(p7, p8);

		Point intersection;
		EXPECT_TRUE(l1.GetLineLineIntersectionPoint(l2, intersection));
		EXPECT_DOUBLE_EQ(round_4_decimal(intersection.x), 2.0496);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersection.y), 2.4463);

		EXPECT_TRUE(l1.GetLineLineIntersectionPoint(l4, intersection));
		EXPECT_DOUBLE_EQ(round_4_decimal(intersection.x), -1.3);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersection.y), 1.25);

		EXPECT_FALSE(l3.GetLineLineIntersectionPoint(l4, intersection));
		EXPECT_FALSE(l4.GetLineLineIntersectionPoint(l3, intersection));
	}
	TEST(LineTest, InvalidLineIntersectionTest)
	{
		const Line l1(Point( 3,4 ), Point( 3,4 ));
		const Line l2(Point( 5,6 ), Point( 5,6 ));

		Point intersection;
		EXPECT_FALSE(l1.GetLineLineIntersectionPoint(l2,intersection));
		EXPECT_FALSE(l2.GetLineLineIntersectionPoint(l1, intersection));

		const Line l3(Point(34, 5), Point(10, -6));
		EXPECT_FALSE(l1.GetLineLineIntersectionPoint(l3, intersection));
		EXPECT_FALSE(l2.GetLineLineIntersectionPoint(l3, intersection));
		EXPECT_FALSE(l3.GetLineLineIntersectionPoint(l1, intersection));
		EXPECT_FALSE(l3.GetLineLineIntersectionPoint(l2, intersection));
	}
	TEST(LineTest, EqualLineIntersectionTest)
	{
		const Line l1(Point(3, 4), Point(13, 14));
		const Line l2(l1);

		Point intersection;
		EXPECT_FALSE(l1.GetLineLineIntersectionPoint(l2, intersection));
		EXPECT_FALSE(l2.GetLineLineIntersectionPoint(l1, intersection));
	}
	TEST(LineTest, LinesWithMutualPointIntersectionTest)
	{
		Point mutual_point(-7, 23);
		const Line l1(Point(3, 4), mutual_point);
		const Line l2(mutual_point, Point(-4, 20));

		Point intersection;
		EXPECT_TRUE(l1.GetLineLineIntersectionPoint(l2, intersection));
		EXPECT_DOUBLE_EQ(intersection.x, mutual_point.x);
		EXPECT_DOUBLE_EQ(intersection.y, mutual_point.y);

		const Line l3(mutual_point, Point(7,-1));
		const Line l4(mutual_point, Point(2, -11));
		intersection.x = 0;
		intersection.y = 0;
		EXPECT_TRUE(l3.GetLineLineIntersectionPoint(l4, intersection));
		EXPECT_DOUBLE_EQ(intersection.x, mutual_point.x);
		EXPECT_DOUBLE_EQ(intersection.y, mutual_point.y);
	}
	TEST(LineTest, NearEpsilonPointIntersectionTest)
	{
		
		const Line l1(Point(3, -4), Point(12.12342663, 20));
		const Line l2(Point(12.12342664,20.0), Point(6, -13));

		Point intersection;
		EXPECT_FALSE(l1.GetLineLineIntersectionPoint(l2, intersection));
	}
	TEST(CircleTest, EQTest)
	{
		const Circle c1(0, 0, 5);
		const Circle c2 = c1;
		EXPECT_EQ(c1, c2);

		const Circle c3(0, 0, 6);
		EXPECT_FALSE(c1 == c3);

		const Circle c4(1, 0, 7);
		const Circle c5(2, 0, 7);
		EXPECT_FALSE(c4 == c5);
	}
	TEST(CircleTest, IntersectionTest)
	{
		const Circle c1(0, 0, 5);
		const Circle c2(3, 2, 7);
		vector<Point> intersections = c1.GetCircleCircleIntersectionPoints(c2);
		EXPECT_EQ(intersections.size(), 2);

		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 1.372);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), -4.8081);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[1].x), -3.9105);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[1].y), 3.1158);

		intersections.clear();

		const Point p1(-3, -3);
		const Point p2(-1, 2);
		const Line l1(p1, p2);

		intersections = c1.GetCircleLineIntersectionPoints(l1);
		EXPECT_EQ(intersections.size(), 0);

		intersections = c2.GetCircleLineIntersectionPoints(l1);
		EXPECT_EQ(intersections.size(), 1);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), -2.6519);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), -2.1298);
		intersections.clear();

		const Circle c3(8, 2, 2);
		intersections = c3.GetCircleCircleIntersectionPoints(c2);
		EXPECT_EQ(intersections.size(), 1);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 10.0);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), 2.0);

		const Circle c4(3, -6, 1);
		intersections.clear();
		intersections = c4.GetCircleCircleIntersectionPoints(c2);
		EXPECT_EQ(intersections.size(), 1);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 3.0);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), -5.0);

		const Circle c5(1, 1, 1);
		const Line l2(Point(0, 0), Point(2, 0));
		intersections.clear();
		intersections = c5.GetCircleLineIntersectionPoints(l2);
		EXPECT_EQ(intersections.size(), 1);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 1.0);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), 0.0);

		const Line l3(Point(1, 0), Point(1, -1));
		intersections.clear();
		intersections = c5.GetCircleLineIntersectionPoints(l3);
		EXPECT_EQ(intersections.size(), 1);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 1.0);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), 0.0);

		const Line l4(Point(1, 0), Point(1, 1));
		intersections.clear();
		intersections = c5.GetCircleLineIntersectionPoints(l4);
		EXPECT_EQ(intersections.size(), 1);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 1.0);
		EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), 0.0);
	}
	TEST(CircleTest, InvalidTest)
	{
		const Circle c1(0, 0, 5);
		const Circle c2(3, 2, 0);
		vector<Point> intersections = c1.GetCircleCircleIntersectionPoints(c2);
		EXPECT_EQ(intersections.size(), 0);
		intersections = c2.GetCircleCircleIntersectionPoints(c1);
		EXPECT_EQ(intersections.size(), 0);

		const Circle c3(0, 0, 10);
		const Circle c4(1, 2, 1);
		intersections.clear();
		intersections = c3.GetCircleCircleIntersectionPoints(c4);
	}
	TEST(PointCloudTest, GetConvexHullTest)
	{
		for (int i = 0; i < 2; ++i)
		{
			int shapes_count;
			vector<Circle> circles;
			vector<Line> lines;
			vector<Point> points;
			vector<Point> expected_points;
			vector<Point> expected_convex_points;
			ifstream input("../ConvexHullOfIntersections/input" + to_string(i) + ".txt");
			ifstream expected_input("../ConvexHullOfIntersections/expected_intersection_points" + to_string(i) + ".txt");
			ifstream expected_hull_input("../ConvexHullOfIntersections/expected_convex_hull_points" + to_string(i) + ".txt");
			input >> shapes_count;
			string sline;

			EXPECT_TRUE(input.is_open());

			ASSERT_GT(shapes_count, 0);

			std::getline(input, sline);
			for (int i = 0; i < shapes_count; i++)
			{
				std::getline(input, sline);
				stringstream linestream(sline);
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

			input.close();
			int exp_points_count;
			expected_input >> exp_points_count;
			std::getline(expected_input, sline);
			for (int i = 0; i < exp_points_count; i++)
			{
				std::getline(expected_input, sline);
				stringstream linestream(sline);
				double x, y;
				linestream >> x >> y;
				Point p(x, y);
				expected_points.push_back(p);
			}

			int exp_hull_points_count;
			expected_hull_input >> exp_hull_points_count;
			std::getline(expected_hull_input, sline);
			for (int i = 0; i < exp_hull_points_count; i++)
			{
				std::getline(expected_hull_input, sline);
				stringstream linestream(sline);
				double x, y;
				linestream >> x >> y;
				Point p(x, y);
				expected_convex_points.push_back(p);
			}
			ASSERT_EQ(expected_points.size(), exp_points_count);
			ASSERT_EQ(expected_convex_points.size(), exp_hull_points_count);

			for (unsigned i = 0; i < lines.size(); i++)
			{
				if (i + 1 >= lines.size())
					continue;

				for (unsigned j = i + 1; j < lines.size(); j++)
				{
					Point new_point;
					if (lines[i].GetLineLineIntersectionPoint(lines[j], new_point))
						points.push_back(new_point);
				}
			}
			for (unsigned i = 0; i < circles.size(); i++)
			{
				if (i + 1 >= circles.size())
					continue;

				for (unsigned j = i + 1; j < circles.size(); j++)
				{
					vector<Point> new_points = circles[i].GetCircleCircleIntersectionPoints(circles[j]);
					points.insert(points.end(), new_points.begin(), new_points.end());
				}
			}
			for (auto circle : circles)
			{
				for (auto line : lines)
				{
					vector<Point> new_points = circle.GetCircleLineIntersectionPoints(line);
					points.insert(points.end(), new_points.begin(), new_points.end());
				}
			}

			EXPECT_EQ(points.size(), exp_points_count);
			vector<Point> not_found;
			for (auto i : points)
			{
				Point tmp(round_4_decimal(i.x), round_4_decimal(i.y));
				auto it = find(expected_points.begin(), expected_points.end(), tmp);
				if (it != expected_points.end())
					expected_points.erase(it);
				else
					not_found.push_back(tmp);
			}
			EXPECT_EQ(expected_points.size(), 0);
			EXPECT_EQ(not_found.size(), 0);


			PointCloud p(points);

			vector<Point> convex_hull_points = p.GetConvexHull();
			EXPECT_EQ(convex_hull_points.size(), exp_hull_points_count);
			vector<Point> not_found_convex;
			vector<Point> area;
			for (const auto& i : convex_hull_points)
			{
				Point tmp(round_4_decimal(i.x), round_4_decimal(i.y));
				auto it = find(expected_convex_points.begin(), expected_convex_points.end(), tmp);
				if (it != expected_convex_points.end())
				{
					area.push_back(*it);
					expected_convex_points.erase(it);
				}
				else
					not_found_convex.push_back(tmp);
			}
			EXPECT_EQ(expected_points.size(), 0);
			EXPECT_EQ(not_found.size(), 0);
			double exp_area;
			expected_hull_input >> exp_area;
			EXPECT_DOUBLE_EQ(round_4_decimal(p.GetConvexHullArea(area)), exp_area);
		}
	}
	TEST(PointCloudTest, EdgeCaseTest)
	{
		PointCloud p(vector<Point>{});
		vector<Point> convex_hull_points = p.GetConvexHull();
		EXPECT_EQ(convex_hull_points.size(), 0);

		convex_hull_points.clear();
		PointCloud p2(vector<Point>{Point(1,-3)});
		convex_hull_points = p2.GetConvexHull();
		EXPECT_EQ(convex_hull_points.size(), 1);

		convex_hull_points.clear();
		PointCloud p3(vector<Point>{Point(1, -3), Point(1, -3)});
		convex_hull_points = p3.GetConvexHull();
		EXPECT_EQ(convex_hull_points.size(), 2);

		convex_hull_points.clear();
		PointCloud p4(vector<Point>{Point(1, -3), Point(1, -3), Point(2, -1), Point(0, 2)});
		convex_hull_points = p4.GetConvexHull();
		EXPECT_EQ(convex_hull_points.size(), 3);

		convex_hull_points.clear();
		PointCloud p5(vector<Point>{Point(1, 0), Point(4, 0), Point(3, 3), Point(2, 2)});
		convex_hull_points = p5.GetConvexHull();
		EXPECT_EQ(convex_hull_points.size(), 4);
	}
}
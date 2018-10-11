#include "pch.h"
#include "Point.h"
#include "Point.cpp"
#include "Line.h"
#include "Line.cpp"
#include "Circle.h"
#include "Circle.cpp"
#include "Polygon.h"
#include "Polygon.cpp"
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>

using namespace ConvexHull;
using std::runtime_error;
using std::vector;
using std::ifstream;
using std::string;
using std::stringstream;
using std::stack;

inline double round_4_decimal(double f)
{
	return round(f * 10000.0) / 10000.0;
}

std::vector<Point> test_points;

class PolygonTestClass : public ::testing::Test, public Polygon
{
public:
	PolygonTestClass() : Polygon(test_points) {}
	void SetUp(const vector<Point>& p)
	{
		SetPoints(p);
	}
	std::stack<Point> S;
};

TEST_F(PolygonTestClass, get2ndtopTest)
{
	Point p1(0, 1);
	S.push(p1);

	EXPECT_THROW(Get2ndTop(S), runtime_error);
}
TEST_F(PolygonTestClass, GetLowest_y_Index_DeathTest)
{
	Point p1(0, 1), p2(9, -4), p3(6, 3);
	vector<Point> test_v;
	test_v.push_back(p1);
	test_v.push_back(p2);
	test_v.push_back(p3);

	EXPECT_THROW(GetLowest_y_Index(test_v), runtime_error);
}
TEST_F(PolygonTestClass, get_lowest_y_indexTest)
{
	Point p1(0, 1), p2(9, -4), p3(6, 3);
	vector<Point> test_v;
	test_v.push_back(p1);
	test_v.push_back(p2);
	test_v.push_back(p3);
	SetUp(test_v);

	int i = GetLowest_y_Index(test_v);
	Point p4 = test_v[i];
	EXPECT_DOUBLE_EQ(p4.x, 9.0);
	EXPECT_DOUBLE_EQ(p4.y, -4.0);
}
TEST(PolygonTest, GetConvexHullTest)
{
	int shapes_count;
	vector<Circle> circles;
	vector<Line> lines;
	vector<Point> points;
	vector<Point> expected_points;
	vector<Point> expected_convex_points;
	ifstream input("../ConvexHullOfIntersections/input0.txt");
	ifstream expected_input("../ConvexHullOfIntersections/expected_intersection_points0.txt");
	ifstream expected_hull_input("../ConvexHullOfIntersections/expected_convex_hull_points0.txt");
	input >> shapes_count;
	string sline;

	EXPECT_EQ(input.is_open(), true);

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
	std::getline(expected_input, sline);
	for (int i = 0; i < 15; i++)
	{
		std::getline(expected_input, sline);
		stringstream linestream(sline);
		double x, y;
		linestream >> x >> y;
		Point p(x, y);
		expected_points.push_back(p);
	}
	std::getline(expected_hull_input, sline);
	for (int i = 0; i < 9; i++)
	{
		std::getline(expected_hull_input, sline);
		stringstream linestream(sline);
		double x, y;
		linestream >> x >> y;
		Point p(x, y);
		expected_convex_points.push_back(p);
	}
	ASSERT_EQ(expected_points.size(), 15);
	ASSERT_EQ(expected_convex_points.size(), 9);

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
				vector<Point> new_points = circles[i].GetCircleCircleIntersectionPoints(circles[j]);
				points.insert(points.end(), new_points.begin(), new_points.end());
			}
	}
	for (auto circle : circles)
		for (auto line : lines)
		{
			vector<Point> new_points = circle.GetCircleLineIntersectionPoints(line);
			points.insert(points.end(), new_points.begin(), new_points.end());
		}

	EXPECT_EQ(points.size(), 15);
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


	Polygon p(points);

	stack<Point> convex_hull_points = p.GetConvexHull();
	EXPECT_EQ(convex_hull_points.size(), 9);
	vector<Point> not_found_convex;
	vector<Point> area;
	while (!convex_hull_points.empty())
	{
		Point i = convex_hull_points.top();
		Point tmp(round_4_decimal(i.x), round_4_decimal(i.y));
		auto it = find(expected_convex_points.begin(), expected_convex_points.end(), tmp);
		if (it != expected_convex_points.end())
		{
			area.push_back(*it);
			expected_convex_points.erase(it);
		}
		else
			not_found_convex.push_back(tmp);
		convex_hull_points.pop();
	}
	EXPECT_EQ(expected_points.size(), 0);
	EXPECT_EQ(not_found.size(), 0);
	EXPECT_DOUBLE_EQ(round_4_decimal(p.GetConvexHullArea(area)), 140.0774);
}
TEST(PointTest, DistanceTest)
{
	Point p1(12, 5), p2(12, 5);
	EXPECT_EQ(p1.distance(p2), 0);

	Point p3(12, 5), p4(0, 5);
	EXPECT_EQ(p3.distance(p4), 12);
	EXPECT_EQ(p4.distance(p3), 12);

	Point p5(12, 0), p6(12, 5);
	EXPECT_EQ(p6.distance(p5), 5);
	EXPECT_EQ(p5.distance(p6), 5);
}
TEST(PointTest, EQTest)
{
	Point p1(12, 5), p2(12, 5);
	EXPECT_EQ(p1, p2);

	Point p3(0, 5), p4(12, 5);
	EXPECT_EQ(p3 == p4, false);
}
TEST(LineTest, EQTest)
{
	Point p1(12, 5), p2(14, 6);
	Line l1(p1, p2), l2(p1, p2);
	EXPECT_EQ(l1, l2);
	l1.p1.x--;
	EXPECT_EQ(l1 == l2, false);
}
TEST(LineTest, IntersectionTest)
{
	Point p1(-2, 1), p2(12, 6);
	Line l1(p1, p2);
	Point p3(-4, 9), p4(8, -4);
	Line l2(p3, p4);
	Point p5(5, 2), p6(7, 9);
	Line l3(p5, p6);
	Point p7(-3, -3), p8(-1, 2);
	Line l4(p7, p8);

	Point intersection;
	EXPECT_EQ(l1.GetLineLineIntersectionPoints(l2, intersection), true);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersection.x), 2.0496);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersection.y), 2.4463);

	EXPECT_EQ(l1.GetLineLineIntersectionPoints(l4, intersection), true);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersection.x), -1.3);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersection.y), 1.25);

	EXPECT_EQ(l3.GetLineLineIntersectionPoints(l4, intersection), false);
	EXPECT_EQ(l4.GetLineLineIntersectionPoints(l3, intersection), false);
}
TEST(CircleTest, EQTest)
{
	Circle c1(0, 0, 5);
	Circle c2 = c1;
	EXPECT_EQ(c1, c2);

	Circle c3(0, 0, 6);
	EXPECT_EQ(c1 == c3, false);
}
TEST(CircleTest, IntersectionTest)
{
	Circle c1(0, 0, 5), c2(3, 2, 7);
	vector<Point> intersections = c1.GetCircleCircleIntersectionPoints(c2);
	EXPECT_EQ(intersections.size(), 2);

	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 1.372);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), -4.8081);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[1].x), -3.9105);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[1].y), 3.1158);

	intersections = c1.GetCircleCircleIntersectionPoints(c2);
	intersections.clear();

	Point p1(-3, -3), p2(-1, 2);
	Line l1(p1, p2);

	intersections = c1.GetCircleLineIntersectionPoints(l1);
	EXPECT_EQ(intersections.size(), 0);

	intersections = c2.GetCircleLineIntersectionPoints(l1);
	EXPECT_EQ(intersections.size(), 1);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), -2.6519);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), -2.1298);
	intersections.clear();

	Circle c3(8, 2, 2);
	intersections = c3.GetCircleCircleIntersectionPoints(c2);
	EXPECT_EQ(intersections.size(), 1);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].x), 10.0);
	EXPECT_DOUBLE_EQ(round_4_decimal(intersections[0].y), 2.0);
}
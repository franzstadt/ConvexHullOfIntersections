#include <iostream>
#include "Solution.h"
#include "Line.h"
#include <chrono>
#include <vector>
#include "Point.h"

int main()
{
	using namespace ConvexHull;
	
	//Usage: 
	// - if a Solution object is created without any parameters(e.g.: Solution s;) -> the input will be the STD input (cin)
	// - if a Solution object is created with 1 parameter(e.g.:Solution s("input.txt");) -> the input will be the file of given name in parameter
	// - the 2nd and 3rd parameter is created for modultest to check the expected values (see below)
	//Solution s("input.txt", "expected_intersection_points.txt", "expected_convex_hull_points.txt");

	/*
	Line l1(Point{ 0,0 }, Point{ 10,0 });
	Circle c(8, 2, 2);

	Point intersection1,intersection2;
	
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<Point> intersections1 = c.GetCircleLineIntersectionPoints(l1);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "orig intersections:";
	for (const auto&p : intersections1)
		std::cout << "(" << p.x << "," << p.y << ") ";

	std::cout << "\ntime: " << elapsed.count() << "\n";
	
	
	auto start2 = std::chrono::high_resolution_clock::now();
	std::vector<Point> intersections2 = c.GetCircleLineIntersectionPoints2(l1);
	auto finish2 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> elapsed2 = finish2 - start2;
	std::cout << "intersections:";
	for (const auto&p : intersections2)
		std::cout << "(" << p.x << "," << p.y << ") ";

	std::cout << "\ntime: " << elapsed2.count() << "\n";
	

	std::cout << (elapsed.count() < elapsed2.count() ? "winner1" : "winner2") << std::endl;
	*/
	
	try
	{
		ConvexHull::Solution s("input0.txt");
		s.GetIntersectionPoints();
		s.CalculateConvexHull();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	system("pause");
	return 0;
}
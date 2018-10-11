#include <iostream>
#include "Solution.h"
#include "Line.h"
#include <chrono>


int main()
{
	using namespace ConvexHull;
	
	//Usage: 
	// - if a Solution object is created without any parameters(e.g.: Solution s;) -> the input will be the STD input (cin)
	// - if a Solution object is created with 1 parameter(e.g.:Solution s("input.txt");) -> the input will be the file of given name in parameter
	// - the 2nd and 3rd parameter is created for modultest to check the expected values (see below)
	//Solution s("input.txt", "expected_intersection_points.txt", "expected_convex_hull_points.txt");


	Line l1(Point{ -2,1 }, Point{ 12,6 });
	Line l2(Point{ -4,9 }, Point{ 8,-4 });

	Point intersection1,intersection2;


	auto start = std::chrono::high_resolution_clock::now();
	l2.GetLineLineIntersectionPoints(l1, intersection1);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "intersect:" << intersection1.x << " " << intersection1.y << "\ntime: " << elapsed.count() << "\n";


	auto start2 = std::chrono::high_resolution_clock::now();
	l2.GetLineLineIntersectionPoints2(l1, intersection2);
	auto finish2 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> elapsed2 = finish2 - start2;
	std::cout << "intersect:" << intersection2.x << " " << intersection2.y << "\ntime: " << elapsed2.count() << "\n";

	std::cout << (elapsed.count() < elapsed2.count() ? "winner1" : "winner2") << std::endl;

	/*
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
	*/
	system("pause");
	return 0;
}
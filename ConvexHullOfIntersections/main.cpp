#include <iostream>
#include "Solution.h"
#include "Line.h"
#include <chrono>
#include <vector>
#include "Point.h"

int main()
{
	
	//Usage: 
	// - if a Solution object is created without any parameters(e.g.: Solution s;) -> the input will be the STD input (cin)
	// - if a Solution object is created with 1 parameter(e.g.:Solution s("input.txt");) -> the input will be the file of given name in parameter
	// - the 2nd and 3rd parameter is created for modultest to check the expected values (see below)
	//Solution s("input.txt", "expected_intersection_points.txt", "expected_convex_hull_points.txt");

	
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
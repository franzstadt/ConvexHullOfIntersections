#include <iostream>
#include "Solution.h"

int main()
{
	//Usage: 
	// - if a Solution object is created without any parameters(e.g.: Solution s;) -> the input will be the STD input (cin)
	// - if a Solution object is created with 1 parameter(e.g.:Solution s("input.txt");) -> the input will be the file of given name in parameter

	ConvexHull::Solution s("input0.txt");

	try
	{
		s.ReadInput();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error:" <<e.what() << std::endl;
		system("pause");
		return 1;
	}

	s.GetIntersectionPoints();
	s.CalculateConvexHull();
	
	
	system("pause");
	return 0;
}
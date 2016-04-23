#include <vector>
#include <iostream>
#include <time.h>
#include "Helper.h"
#include "Geometry/Geometry.h"
#include "EllipsoidBuilder.h"
#include "IConvexHullBuilder.h"
#include "ConvHullBuilder.h"
#include "IRectangleBuilder.h"
#include "SimpleRectangleBuilder.h"
#include "MinimumRectangleBuilder.h"

void PrintRanks(std::ofstream & fo, const std::vector<int> & ranks, const std::string & direction, 
	const std::string & centreChosen);

int main()
{
	Helper* helper= new Helper();
	IConvexHullBuilder* convHullBuilder = new ConvHullBuilder();
	IRectangleBuilder* simpleRectangleBuilder = new SimpleRectangleBuilder();
	IRectangleBuilder* minRectangleBuilder = new MinimumRectangleBuilder();
	EllipsoidBuilder* ellipsoidBuilder = new EllipsoidBuilder();

	srand(time(NULL));

	const int NumberOfPoints = 300;
	const int NumberOfLevels = 10;
	const int NumberOfExperiments = 100;

	for (int j = 0; j < NumberOfLevels; ++j)
	{
		int standart = 0, min = 0;
		for (int i = 0; i < NumberOfExperiments; ++i)
		{
			std::vector<Point2D> points = helper->GenRandVertexes(NumberOfPoints, j + 1);
		
			Ellipsoid2D* simpleEl = ellipsoidBuilder->BuildEllipsoid(convHullBuilder, simpleRectangleBuilder, points);
			Ellipsoid2D* minEl = ellipsoidBuilder->BuildEllipsoid(convHullBuilder, minRectangleBuilder, points);

			if (simpleEl == NULL || minEl == NULL)
				continue;
			
			if (simpleEl->Area() < minEl->Area())
			{
				++standart;
			}
			else
			{
				++min;
			}
		
			delete simpleEl;
			delete minEl;
		}

		std::cout << "Lengthiness level: " << j + 1 << "\n\t" << standart << " times Standart was smaller\n\t"<< min << " times Minimum was smaller" << std::endl;
	}

	std::cout << "Press any key.\n";
	std::cin.get();

	delete helper;
	delete convHullBuilder;
	delete simpleRectangleBuilder;
	delete minRectangleBuilder;
	delete ellipsoidBuilder;

	return 0;
}

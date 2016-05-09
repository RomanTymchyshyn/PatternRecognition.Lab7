#include <vector>
#include <iostream>
#include <ctime>
#include "Helper.h"
#include "Geometry/Geometry.h"
#include "EllipsoidBuilder.h"
#include "IConvexHullBuilder.h"
#include "ConvHullBuilder.h"
#include "IRectangleBuilder.h"
#include "SimpleRectangleBuilder.h"
#include "MinimumRectangleBuilder.h"

int main()
{
	Helper* helper= new Helper();
	IConvexHullBuilder* convHullBuilder = new ConvHullBuilder();
	IRectangleBuilder* simpleRectangleBuilder = new SimpleRectangleBuilder();
	IRectangleBuilder* minRectangleBuilder = new MinimumRectangleBuilder();
	EllipsoidBuilder* ellipsoidBuilder = new EllipsoidBuilder();

	std::srand(std::time(NULL));

	const int NumberOfPoints = 300;
	const int NumberOfLevels = 10;
	const int NumberOfExperiments = 100;

	std::cout << NumberOfExperiments << " experiments made for each lengthiness level.\n";

	for (int j = 0; j < NumberOfLevels; ++j)
	{
		int countStandart = 0, countMinimum = 0, equalsCount = 0;
		for (int i = 0; i < NumberOfExperiments; ++i)
		{
			std::vector<Point2D> points = helper->GenRandVertexes(NumberOfPoints, j + 1);

			Ellipsoid2D* simpleEl = ellipsoidBuilder->BuildEllipsoid(convHullBuilder, simpleRectangleBuilder, points);
			Ellipsoid2D* minEl = ellipsoidBuilder->BuildEllipsoid(convHullBuilder, minRectangleBuilder, points);

			if (simpleEl == NULL || minEl == NULL)
				continue;
			
			double simpleArea = simpleEl->Area();
			double minArea = minEl->Area();
			
			if (std::fabs(simpleArea - minArea) < 0.00001)
			{
				++equalsCount;
			}
			else if (simpleArea < minArea)
			{
				++countStandart;
			}
			else
			{
				++countMinimum;
			}
		
			delete simpleEl;
			delete minEl;
		}

		std::cout << "Lengthiness level: " << j + 1 << "\n\t" << equalsCount << " times ellipses were EQUAL\n\t" << countStandart << " times Standart was smaller\n\t"<< countMinimum << " times Minimum was smaller" << std::endl;
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

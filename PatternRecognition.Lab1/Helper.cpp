#include "Helper.h"
#include <cstdlib>

std::vector<Point2D> Helper::GenRandVertexes(int number, int lengthiness)
{
	double min = 0.0;
	int maxY = 100;
	int maxX = maxY * lengthiness;

	double x = 0.0, y = 0.0;
	std::vector<Point2D> points;
	for (int i = 0; i < number; ++i)
	{
		x = (maxX - min) * ((double)std::rand() / RAND_MAX) + min;
		y = (maxY - min) * ((double)std::rand() / RAND_MAX) + min;
		points.push_back(Point2D(x, y));
	}
	return points;
}
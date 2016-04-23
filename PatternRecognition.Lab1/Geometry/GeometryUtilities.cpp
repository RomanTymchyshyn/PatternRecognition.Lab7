#include "GeometryUtilities.h"

std::vector<double> rotate(std::vector<double> a, const double & phi)
{
	double a11 = cos(phi);
	double a12 = sin(phi);
	std::vector< std::vector<double> > matr;
	std::vector< double > result;
	result.push_back(a11);
	result.push_back(a12);
	matr.push_back(result);
	result.clear();
	result.push_back((-1.0) * a12);
	result.push_back(a11);
	matr.push_back(result);
	result.clear();
	result = matr * a;
	return result;
}

bool CheckVectorsCollinearity(const std::vector<double> & v1, const std::vector<double> & v2)
{
	return fabs(v1[0] * v2[1] - v1[1] * v2[0]) < 0.0001;
}

bool CheckVectorsCollinearity(const double & x1, const double & y1, const double & x2, const double & y2)
{
	return fabs(x1 * y2 - y1 * x2) < 0.0001;
}

bool CheckVectorsCollinearity(const Point2D & p1, const Point2D & p2, const Point2D & p3, const Point2D & p4)
{
	double x1 = p2.X() - p1.X();
	double y1 = p2.Y() - p1.Y();

	double x2 = p4.X() - p3.X();
	double y2 = p4.Y() - p3.Y();

	return CheckVectorsCollinearity(x1, y1, x2, y2);
}
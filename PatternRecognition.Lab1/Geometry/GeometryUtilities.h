#pragma once

#include <vector>
#include "Point2D.h"
#define M_PI 3.141592653589793238462643383279502884

template<class T>
std::vector<T> operator*(const std::vector<std::vector<T>> b, const std::vector<T> a)
{
	if (a.size() == 0) return std::vector <T>();
	if (b.size() == 0 || b.size() != int(a.size())) return std::vector<T>();
	std::vector<T> result(b.size(), (T)0);
	for (int i = 0; i < b.size(); ++i)
	{
		T temp = 0;
		for (int j = 0; j < b.size(); ++j)
		{
			temp = b[i][j] * a[j];
			result[i] = result[i] + temp;
			temp = (T)0;
		}
	}
	return result;
};

std::vector<double> rotate(std::vector<double> a, const double & phi);

bool CheckVectorsCollinearity(const std::vector<double> & v1, const std::vector<double> & v2);

bool CheckVectorsCollinearity(const double & x1, const double & y1, const double & x2, const double & y2);

bool CheckVectorsCollinearity(const Point2D & p1, const Point2D & p2, const Point2D & p3, const Point2D & p4);
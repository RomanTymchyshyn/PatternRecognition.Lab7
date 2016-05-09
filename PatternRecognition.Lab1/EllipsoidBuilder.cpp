#include "EllipsoidBuilder.h"
#include <algorithm>
#include <fstream>
#include <math.h>

Ellipsoid2D* EllipsoidBuilder::BuildEllipsoid(IConvexHullBuilder* convexHullBuilder, IRectangleBuilder* rectBuilder, const std::vector<Point2D>& input)
{
	std::vector<Point2D> conv = convexHullBuilder->BuildConvHull(input);

	if(conv.size() < 3)
		return NULL;

	reverse(conv.begin(), conv.end()); //counterclockwise

	Rectangle2D rect = rectBuilder->GetRectangle(conv);

	std::vector<double> rectParams;
	std::vector<double> offset;
	double angle;
	GetParameters(rect, offset, rectParams, angle);

	std::vector<Point2D> points = TranslatePoints(conv, offset[0], offset[1]);

	points = RotatePoints(points, angle);

	double alpha = rectParams[1] / rectParams[0];

	points = ScalePoints(points, alpha, 1.0);

	Point2D centre = Point2D(rectParams[1] / 2.0, rectParams[1] / 2.0);

	double R = GetRadius(points, centre);

	std::vector<std::vector<double>> eVectors(2, std::vector<double>(2, 0));
	eVectors[0][0] = 1;
	eVectors[1][1] = 1;

	std::vector<double> axes(2, R);

	Ellipsoid2D* res = new Ellipsoid2D(centre, eVectors, axes);
	
	(*res) = res->Scale(1.0 / alpha, 1.0);

	(*res) = res->Rotate(-angle);

	(*res) = res->Translation(-offset[0], -offset[1]);

	return res;
}

std::vector<Point2D> EllipsoidBuilder::RotatePoints(const std::vector<Point2D> & points, const double & angle)
{
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
		res.push_back(points[i].Rotate(angle));
	return res;
}

std::vector<Point2D> EllipsoidBuilder::TranslatePoints(const std::vector<Point2D> & points, 
	const double & xOffset, const double & yOffset)
{
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
		res.push_back(points[i].Translation(xOffset, yOffset));
	return res;
}

std::vector<Point2D> EllipsoidBuilder::ScalePoints(const std::vector<Point2D> & points, const double & byX, const double & byY)
{
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
		res.push_back(points[i].Scale(byX, byY));
	return res;
}

double EllipsoidBuilder::GetRadius(const std::vector<Point2D> & points, const Point2D & centre)
{
	double max = -1;
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		double dist = points[i].Distance(centre);
		if (dist > max) max = dist;
	}
	return max;
}

void EllipsoidBuilder::GetParameters(const Rectangle2D & rect, std::vector<double> & offset, 
	std::vector<double> & rectParams, double & angle)
{
	int leftBottomIndex = rect.LeftBottomIndex();
	offset.push_back(-rect.Vertex(leftBottomIndex).X());
	offset.push_back(-rect.Vertex(leftBottomIndex).Y());

	int neighbour1 = leftBottomIndex == 0 ? 3 : leftBottomIndex - 1;
	int neighbour2 = leftBottomIndex == 3 ? 0 : leftBottomIndex + 1;
	int secondPoint = rect.Vertex(neighbour1).X() > rect.Vertex(neighbour2).X() ? neighbour1 : neighbour2;
	double a1 = rect.Vertex(secondPoint).X() - rect.Vertex(leftBottomIndex).X();
	double a2 = rect.Vertex(secondPoint).Y() - rect.Vertex(leftBottomIndex).Y();
	angle = std::acos(a1 / sqrt(a1 * a1 + a2 * a2));
	if (a2 < 0) angle *= -1.0;
	
	rectParams.push_back(rect.Vertex(secondPoint).Distance(rect.Vertex(leftBottomIndex)));
	rectParams.push_back(rect.Vertex(secondPoint == neighbour1 ? neighbour2 : neighbour1).Distance( 
		rect.Vertex(leftBottomIndex)));
}
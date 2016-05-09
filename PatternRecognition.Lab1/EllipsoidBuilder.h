#pragma once

#include <vector>
#include "Geometry/Geometry.h"
#include "IRectangleBuilder.h"
#include "ConvHullBuilder.h"

enum DirectionOfCompression { Left, Right, Centre };

class EllipsoidBuilder
{
	public:

		Ellipsoid2D* BuildEllipsoid(IConvexHullBuilder* convexHullBuilder, IRectangleBuilder* rectBuilder, const std::vector<Point2D>& points);

	private:

		std::vector<Point2D> RotatePoints(const std::vector<Point2D> & points, const double & angle);

		std::vector<Point2D> TranslatePoints(const std::vector<Point2D> & points, const double & xOffset, 
			const double & yOffset);

		std::vector<Point2D> ScalePoints(const std::vector<Point2D> & points, const double & byX, const double & byY);

		void GetParameters(const Rectangle2D & rect, std::vector<double> & offset, 
			std::vector<double> & rectParams, double & angle);

		double GetRadius(const std::vector<Point2D> & points, const Point2D & centre);
};
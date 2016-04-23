#pragma once

#include "IRectangleBuilder.h"
#include "Geometry\Geometry.h"

class SimpleRectangleBuilder: public IRectangleBuilder
{
	public:

		virtual Rectangle2D GetRectangle(const std::vector<Point2D> & convexHull) const;

	private:

		void FindFarthestPair(const std::vector<Point2D> & points, Point2D & diag1, 
			Point2D & diag2, double & distance) const;

		void FindFarthestFromLine(Line2D l, const std::vector<Point2D> & points, Point2D & top, 
			Point2D & bottom, double & maxTop, double & maxBot) const;
};
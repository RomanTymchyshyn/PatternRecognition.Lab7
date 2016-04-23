#pragma once

#include "IRectangleBuilder.h"
#include "Geometry\Geometry.h"

class MinimumRectangleBuilder: public IRectangleBuilder
{
	public:

		virtual Rectangle2D GetRectangle(const std::vector<Point2D> & convexHull) const;

	private:

		double Angle(const std::vector<Point2D> conv, const int & i) const;

};
#pragma once

#include "Geometry\Geometry.h"

class IRectangleBuilder
{
	public:

		virtual Rectangle2D GetRectangle(const std::vector<Point2D> & convexHull) const = 0;
};
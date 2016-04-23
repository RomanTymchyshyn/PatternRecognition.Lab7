#pragma once

#include "Geometry\Geometry.h"

class IConvexHullBuilder
{
	public:

		virtual std::vector<Point2D> BuildConvHull(const std::vector<Point2D> & points) const  = 0;

};
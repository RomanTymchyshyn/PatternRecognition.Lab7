#pragma once

#include "Geometry\Geometry.h"
#include "IConvexHullBuilder.h"

class ConvHullBuilder: public IConvexHullBuilder
{
	public:

		virtual std::vector<Point2D> BuildConvHull(const std::vector<Point2D> & points) const;

		std::vector<Point2D> BuildConvHull(const std::vector<Point2D> & points, Point2D & left, Point2D & right, Point2D & up, Point2D & bot) const;

	private:

		std::vector<Point2D> BuildRecursive(const std::vector<Point2D> & vertexes, const Point2D & left, const Point2D & right, Point2D & top) const;
};
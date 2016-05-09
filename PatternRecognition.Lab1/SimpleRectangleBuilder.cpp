#include "SimpleRectangleBuilder.h"

Rectangle2D SimpleRectangleBuilder::GetRectangle(const std::vector<Point2D> & points) const
{
	Point2D left, right;
	double distance = 0.0;
	FindFarthestPair(points, left, right, distance);

	Line2D L(left, right);
	Point2D top(left), bottom(right);
	double maxTopDist, maxBotDist;
	FindFarthestFromLine(L, points, top, bottom, maxTopDist, maxBotDist);

	if (top == left)
		top = left.Y() > right.Y() ? left : right;
	if (bottom == right)
		bottom = left.Y() < right.Y() ? left : right;

 	Line2D L1 = L.GetParallel(top);
	Line2D L2 = L.GetParallel(bottom);
	Line2D L3 = L.GetPerpendicular(left);
	Line2D L4 = L.GetPerpendicular(right);

	Point2D p1 = L1.Intersection(L3);
	Point2D p2 = L1.Intersection(L4);
	Point2D p3 = L2.Intersection(L4);
	Point2D p4 = L2.Intersection(L3);

	Rectangle2D rect = Rectangle2D(p1, p2, p3, p4);

	return rect;
}

void SimpleRectangleBuilder::FindFarthestPair(const std::vector<Point2D> & points, Point2D & diag1, 
	Point2D & diag2, double & distance) const
{
	int n = points.size();
	distance = -1;
	for (int i = 0; i < n; ++i)
	{
		Point2D p1 = points[i];
		for (int j = i + 1; j < n; ++j)
		{
			Point2D p2 = points[j];
			double dist = p1.Distance(p2);
			if (dist > distance)
			{
				diag1 = p1;
				diag2 = p2;
				distance = dist;
			}
		}
	}
	return;
}

void SimpleRectangleBuilder::FindFarthestFromLine(Line2D l, const std::vector<Point2D> & points, Point2D & top, 
	Point2D & bottom, double & maxTop, double & maxBot) const
{
	int n = points.size();
	maxTop = -1, maxBot = -1;
	for (int i = 0; i < n; ++i)
	{
		Point2D p = points[i];
		double dist = l.Distance(p);
		int deviation = l.Deviation(p);
		if (deviation == -1)
		{
			if (dist > maxTop)
			{
				top = p;
				maxTop = dist;
			}
		}
		else if (deviation == 1)
		{
			if (dist > maxBot)
			{
				bottom = p;
				maxBot = dist;
			}
		}
	}
	return;
}
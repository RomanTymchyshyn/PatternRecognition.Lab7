#include "MinimumRectangleBuilder.h"
#include <math.h> 

double MinimumRectangleBuilder::Angle(const std::vector<Point2D> conv, const int & i) const
{
	int n = conv.size();

	double x1 = conv[i % n].X() - conv[(i - 1 + n) % n].X();
	double y1 = conv[i % n].Y() - conv[(i - 1 + n) % n].Y();

	double x2 = conv[(i + 1) % n].X() - conv[i % n].X();
	double y2 = conv[(i + 1) % n].Y() - conv[i % n].Y();

	double angle = std::acos((x1*x2 + y1*y2)/(std::sqrt(x1*x1 + y1*y1) * std::sqrt(x2*x2 + y2*y2)));

	return angle;
}

Rectangle2D MinimumRectangleBuilder::GetRectangle(const std::vector<Point2D> & conv) const
{	
	double alpha = 0.0, beta = Angle(conv, 1), gamma = beta, delta = beta;
	int j = 1, k = 1, m = 1;

	int n = conv.size();
	double minArea = 0.0;
	
	Rectangle2D minRect;

	for (int i = 0; i < n; ++i)
	{
		if (i > 0)
			alpha += Angle(conv, i);

		while (beta < alpha + M_PI / 2)
		{
			j = (++j) % n;
			beta += Angle(conv, j);
		}

		while (gamma < alpha + M_PI)
		{
			k = (++k) % n;
			gamma += Angle(conv, k);
		}

		while (delta < alpha + 3 * M_PI / 2)
		{
			m = (++m) % n;
			delta += Angle(conv, m);
		}

		Line2D l1(conv[i], conv[(i + 1) % n]);
		Line2D l2 = l1.GetPerpendicular(conv[j]);
		Line2D l3 = l1.GetParallel(conv[k]);
		Line2D l4 = l1.GetPerpendicular(conv[m]);

		Rectangle2D rect(l1.Intersection(l2), l2.Intersection(l3), l3.Intersection(l4), l4.Intersection(l1));

		double area = rect.Area();

		if (i == 0 || area < minArea)
		{
			minRect = rect;
			minArea = area;
		}
	}
	
	return minRect;
}
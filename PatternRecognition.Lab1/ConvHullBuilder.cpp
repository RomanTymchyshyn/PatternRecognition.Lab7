#include "ConvHullBuilder.h"
#include <algorithm>

std::vector<Point2D> ConvHullBuilder::BuildRecursive(const std::vector<Point2D> & vertexes, const Point2D & left, const Point2D & right, Point2D & top) const
{
	std::vector<Point2D> points(vertexes);
	int points_size = points.size();
	if (points_size < 2) return points;
	top = points.at(0);
	Line2D base_edge(left, right);
	
	double dist = base_edge.Distance(top);
	for (int i = 1; i < points_size; ++i)
	{
		double temp_dist = base_edge.Distance(points.at(i));
		if (temp_dist > dist)
		{
			top = points.at(i);
			dist = temp_dist;
		}
		else
			if (temp_dist == dist)
			{
				Line2D l1(left, top);
				if (l1.Deviation(points.at(i)) != l1.Deviation(right))
				{
					top = points.at(i);
					dist = temp_dist;
				}
			}
	}

	std::vector<Point2D> S1;
	std::vector<Point2D> S2;
	Line2D edge1(left, top);
	Line2D edge2(right, top);

	int dev = edge1.Deviation(right);
	for (int i = 0; i < points_size; ++i)
		if (points.at(i) != top && edge1.Deviation(points.at(i)) != dev)
			S1.push_back(points.at(i));

	dev = edge2.Deviation(left);
	for (int i = 0; i < points_size; ++i)
		if (points.at(i) != top && edge2.Deviation(points.at(i)) != dev)
			S2.push_back(points.at(i));

	std::vector<Point2D> result = BuildRecursive(S1, left, top, Point2D());
	result.push_back(top);
	std::vector<Point2D> temp_res = BuildRecursive(S2, top, right, Point2D());
	for (int i = 0; i < (int)temp_res.size(); ++i)
		result.push_back(temp_res.at(i));
		
	return result;
}

bool Compare_Points_by_X(const Point2D & p1, const Point2D & p2)
{
	return p1.X() < p2.X();
};

std::vector<Point2D> Sort_by_X(const std::vector<Point2D> & points)
{
	std::vector<Point2D> sorted_points(points);
	std::sort(sorted_points.begin(), sorted_points.end(), Compare_Points_by_X);
	return sorted_points;
}

std::vector<Point2D> ConvHullBuilder::BuildConvHull(const std::vector<Point2D> & points, Point2D & left, Point2D & right, Point2D & up, Point2D & bot) const
{
	std::vector<Point2D> conv;
	std::vector<Point2D> sorted = Sort_by_X(points);

	if (points.size() < 3) return conv;
	int size_of_sorted = sorted.size();
	left = sorted.at(0);
	right = sorted.at(size_of_sorted - 1);
	std::vector<Point2D> top;
	std::vector<Point2D> bottom;
	Line2D base_edge(left, right);

	for (int i = 0; i < size_of_sorted; ++i)
	{
		if (base_edge.Deviation(sorted.at(i)) == -1) {
				bottom.push_back(sorted.at(i));
		}
		else {
			if (base_edge.Deviation(sorted.at(i)) == 1) {
				top.push_back(sorted.at(i));
			}
		}
	}
	
	conv.push_back(left);

	std::vector<Point2D> conv_part1(BuildRecursive(top, left, right, up));

	for (int i = 0; i < (int)conv_part1.size(); ++i)
	{
		conv.push_back(conv_part1.at(i));
	}
	conv.push_back(right);

	std::vector<Point2D> conv_part2(BuildRecursive(bottom, left, right, bot));
	reverse(conv_part2.begin(), conv_part2.end());
	for (int i = 0; i < (int)conv_part2.size(); ++i)
	{
		conv.push_back(conv_part2.at(i));
	}
	
	return conv;
}

std::vector<Point2D> ConvHullBuilder::BuildConvHull(const std::vector<Point2D> & points) const
{
	std::vector<Point2D> result = BuildConvHull(points, Point2D(), Point2D(), Point2D(), Point2D());

	int sizeOfConv = result.size();
	for (int i = 1; i < sizeOfConv + 1; ++i)
	{
		if (CheckVectorsCollinearity(result[i % sizeOfConv], result[i - 1], result[i % sizeOfConv], result[(i + 1) % sizeOfConv]))
		{
			result.erase(result.begin() + (i % sizeOfConv));
			--i;
			--sizeOfConv;
		}
	}

	return result;
}
#pragma once

class Point2D
{
	public:

		Point2D(double x = 0.0, double y = 0.0): _x(x), _y(y) {};

		Point2D(const Point2D& p): _x(p.X()), _y(p.Y()) {};
		
		double X() const { return _x; };

		double Y() const { return _y; };

		Point2D Rotate(const double & angle) const;

		Point2D Scale(const double & xCoef, const double & yCoef) const { return Point2D(this->X() * xCoef, this->Y() * yCoef);};

		Point2D Translation(const double & byX, const double & byY) const { return Point2D(this->X() + byX, this->Y() + byY); };

		double Distance(const Point2D & p2) const;

	private:

		double _x;

		double _y;
};

bool operator==(const Point2D & p1, const Point2D & p2);

bool operator!=(const Point2D & p1, const Point2D & p2);
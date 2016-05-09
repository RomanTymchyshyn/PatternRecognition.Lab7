#include "Ellipsoid2D.h"
#include <math.h>

Ellipsoid2D::Ellipsoid2D(const Ellipsoid2D & e)
{
	_eigenvectors = e._eigenvectors;
	_axes = e._axes;
	if (e._centre != NULL) _centre = new Point2D(*e._centre);
	else _centre = new Point2D();
}

Ellipsoid2D::Ellipsoid2D(const Point2D & centre, const std::vector<std::vector<double>> & eigenvectors, const std::vector<double> & axes)
{
	_centre = new Point2D(centre);
	_eigenvectors = eigenvectors;
	_axes = axes;
}

double Ellipsoid2D::Eigenvectors(const int & i, const int & j) const
{
	if (i < 0 || i >= _eigenvectors.size() || j < 0 || j >= _eigenvectors[0].size()) return 0.0; 
	return _eigenvectors[i][j];
}

double Ellipsoid2D::Axes(const int & i) const
{
	if (i < 0 || i >= _axes.size()) return -1.0;
	return _axes[i];
}

Ellipsoid2D Ellipsoid2D::Rotate(const double& angle)
{
	std::vector<double> e1(2, 0);
	e1[0] = Eigenvectors(0, 0);
	e1[1] = Eigenvectors(1, 0);

	std::vector<double> e2(2, 0);
	e2[0] = Eigenvectors(0, 1);
	e2[1] = Eigenvectors(1, 1);
	
	e1 = rotate(e1, angle);
	e2 = rotate(e2, angle);
	
	std::vector<std::vector<double>> eigenvectors(2, std::vector<double>(2, 0));
	eigenvectors[0][0] = e1[0];
	eigenvectors[1][0] = e1[1];
	eigenvectors[0][1] = e2[0];
	eigenvectors[1][1] = e2[1];

	Point2D rotatedCentre = this->Centre().Rotate(angle);
	
	return Ellipsoid2D(rotatedCentre, eigenvectors, Axes());
}

Ellipsoid2D Ellipsoid2D::Scale(const double& xCoef, const double& yCoef)
{
	Point2D centre = this->Centre().Scale(xCoef, yCoef);
	std::vector<double> axes(2, 0);

	std::vector<double> e1(2, 0);
	e1[0] = this->Eigenvectors(0, 0);
	e1[1] = this->Eigenvectors(1, 0);
	
	std::vector<double> xAxe(2, 0);
	xAxe[0] = 1;
	xAxe[1] = 0;
	
	double x = 0.0, y = 0.0;
	x = this->Axes()[0];
	y = this->Axes()[1];
	if (CheckVectorsCollinearity(e1, xAxe))
	{
		axes[0] = x * xCoef;
		axes[1] = y * yCoef;
	}
	else
	{
		axes[0] = x * yCoef;
		axes[1] = y * xCoef;
	}
	return Ellipsoid2D(centre, this->Eigenvectors(), axes);
}

Ellipsoid2D Ellipsoid2D::Translation(const double& byX, const double& byY)
{
	Point2D centre = this->Centre().Translation(byX, byY);
	return Ellipsoid2D(centre, this->Eigenvectors(), this->Axes());
}

bool Ellipsoid2D::Inside(const Point2D & p)
{
	double angle = std::acos(this->Eigenvectors(0, 0) / sqrt(this->Eigenvectors(0,0) * this->Eigenvectors(0,0)
												  + this->Eigenvectors(1,0) * this->Eigenvectors(1,0)));//angle between (1,0)
																										//and eigenvector which 
																										//corresponds axe a
	if (this->Eigenvectors(1,0) < 0) angle*=(-1.0);

	Point2D temp = Point2D(p.X() - this->Centre().X(), p.Y() - this->Centre().Y());
	Point2D current = temp.Rotate(angle);

	if (((current.X()*current.X())/(this->Axes(0)*this->Axes(0)) + (current.Y()*current.Y())/(this->Axes(1)*this->Axes(1))) > 1.0 + 0.001) return false;
	return true;
}

Ellipsoid2D::~Ellipsoid2D()
{
	if (_centre != NULL) 
	{
		delete _centre;
		_centre = NULL;
	}
}

Ellipsoid2D& Ellipsoid2D::operator=(const Ellipsoid2D & rhs)
{
	_centre = new Point2D(rhs.Centre());
	_eigenvectors = rhs.Eigenvectors();
	_axes = rhs.Axes();
	return (*this);
}
#pragma once

#include <vector>
#include "Point2D.h"
#include "GeometryUtilities.h"

class Ellipsoid2D
{
	private:
		Point2D* _centre;

		std::vector<std::vector<double>> _eigenvectors;//column i corresponds to the eigenvector number i
		
		std::vector<double> _axes;//axe i corresponds to the eigenvector number i
			
	public:
				
		Ellipsoid2D(const Ellipsoid2D & e);
		
		Ellipsoid2D(const Point2D & centre, const std::vector<std::vector<double>> & eigenvectors, const std::vector<double> & axes);
		
		Point2D Centre() const { if (_centre != NULL) return *_centre; else return Point2D(); };
		
		std::vector<std::vector<double>> Eigenvectors() const { return _eigenvectors; };
		
		std::vector<double> Axes() const { return _axes; };
		
		double Eigenvectors(const int & i, const int & j) const;
		
		double Axes(const int & i) const;
		
		double Area() const { return M_PI*_axes[0]*_axes[1]; }
		
		int Dim() const { return 2; }
		
		Ellipsoid2D Rotate(const double & angle);
		
		Ellipsoid2D Scale(const double & xCoef, const double & yCoef);
		
		Ellipsoid2D Translation(const double & byX, const double & byY);
		
		~Ellipsoid2D();
		
		Ellipsoid2D& operator=(const Ellipsoid2D & e);
		
		bool Inside(const Point2D & p);//returns true if the point is inside ellipse
};
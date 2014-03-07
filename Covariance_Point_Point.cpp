# include "Covariance_Point_Point.h"
# include <math.h>

double Covariance_Point_Point(const double &xi, const double &yi, const double &zi, const double &xj, const double &yj, const double &zj, const double &range, const double &contribution){

	double dx = xi-xj;
	double dy = yi-yj;
	double dz = zi-zj;

	double h = sqrt((dx*dx)+(dy*dy)+(dz*dz));

	double divisor_auxiliar = h/range;// auxiliar variable to help calculating the covariances
	double variogram = 0;
	double cova_point_point = 0;

	if (h<=range){
		variogram = (1.5*divisor_auxiliar)-(0.5*(divisor_auxiliar*divisor_auxiliar*divisor_auxiliar));
		cova_point_point = contribution*(1-variogram);
	}
	else{
		variogram = 1;
		cova_point_point = contribution*(1-variogram);
	}

	return cova_point_point;
}
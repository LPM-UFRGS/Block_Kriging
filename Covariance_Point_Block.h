#ifndef COVARIANCE_POINT_BLOCK_H
#define COVARIANCE_POINT_BLOCK_H
# include <vector>

double Covariance_Point_Block(const double &xi , const double &yi, const double &zi, const std::vector<std::vector<double> > &blockj, const double &range, const double &contribution);


#endif
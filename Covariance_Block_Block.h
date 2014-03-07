#ifndef COVARIANCE_BLOCK_BLOCK_H
#define COVARIANCE_BLOCK_BLOCK_H

# include "Covariance_Point_Point.h"
# include <vector>


double Covariance_Block_Block(const std::vector<std::vector<double> > &blocki, const std::vector<std::vector<double> > &blockj, const double &range, const double &contribution);


#endif
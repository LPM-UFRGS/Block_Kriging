#ifndef BUILD_LHS_COVARIANCE_MATRIX_H
#define BUILD_LHS_COVARIANCE_MATRIX_H
# include <vector>

std::vector<std::vector<double> > Build_LHS_Covariance_Matrix(const std::vector<std::vector<double> > &samples, const std::vector<std::vector<double> > &block, const double &range, const double &contribution, const int &kriging_option);


#endif
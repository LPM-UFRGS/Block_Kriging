#ifndef BUILD_RHS_COVARIANCE_MATRIX_H
#define BUILD_RHS_COVARIANCE_MATRIX_H
# include <vector>

std::vector<double> Build_RHS_Covariance_Matrix(const std::vector<std::vector<double> > &samples, const std::vector<std::vector<double> > &block, const double &xu, const double &yu, const double &zu, const double &range, const double &contribution, const int &kriging_option);


#endif
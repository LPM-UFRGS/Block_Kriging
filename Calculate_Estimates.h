#ifndef CALCULATE_ESTIMATES_H
#define CALCULATE_ESTIMATES_H
# include <vector>

double Calculate_Estimates(const std::vector<std::vector<double> > &samples, const double &block_value, const std::vector<double> &Kriging_Weigths, const int &kriging_option, const double SK_mean);


#endif
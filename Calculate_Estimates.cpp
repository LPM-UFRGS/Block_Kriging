# include "Calculate_Estimates.h"
# include <vector>

using namespace std;


double Calculate_Estimates(const std::vector<std::vector<double> > &samples, const double &block_value, const std::vector<double> &Kriging_Weights, const int &kriging_option, const double SK_mean)
{
	double estimate = 0;
	if (kriging_option == 0){
		for (size_t i = 0; i < Kriging_Weights.size(); ++i){
		
				if (i < samples.size()){
					estimate = estimate + Kriging_Weights[i]*(samples[i][3]-SK_mean);
				}
				else {
					estimate = estimate + Kriging_Weights[i]*(block_value-SK_mean);
				}
		}
	}
	else {
		for (size_t i = 0; i < Kriging_Weights.size()-1; ++i){
			if (i < samples.size()){
					estimate = estimate + Kriging_Weights[i]*samples[i][3];
			}
			else {
					estimate = estimate + Kriging_Weights[i]*block_value;
			}
		}
	}

	if (kriging_option == 0)
		estimate = estimate + SK_mean;

	return estimate;
}
# include "Covariance_Point_Point.h"
# include "Covariance_Point_Block.h"
# include <vector>

using namespace std;

std::vector<double> Build_RHS_Covariance_Matrix (const std::vector<std::vector<double> > &samples, const std::vector<std::vector<double> > &block, const double &xu, const double &yu, const double &zu, const double &range, const double &contribution, const int &kriging_option){
	vector<double> RHS_Covariance_Matrix; // Define the matrix which will receive the covariances
	// Add Covariance Point_Sample_Point_to_be_estimated
	for(size_t i = 0; i < samples.size(); ++i){
		double covariance_point_sample_point_to_be_estimated = Covariance_Point_Point(samples[i][0], samples[i][1], samples[i][2], xu, yu, zu, range, contribution);
			RHS_Covariance_Matrix.push_back(covariance_point_sample_point_to_be_estimated);
	}
	// Add Covariance Block_Sample-Point_to_be_estimated
	double covariance_point_to_be_estimated_block = Covariance_Point_Block(xu, yu, zu, block, range, contribution);
	RHS_Covariance_Matrix.push_back(covariance_point_to_be_estimated_block);

	if (kriging_option == 1)
		RHS_Covariance_Matrix.push_back(1.00);
	
	return RHS_Covariance_Matrix;

}
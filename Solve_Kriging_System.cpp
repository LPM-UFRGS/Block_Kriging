# include "Eigen\Dense"
# include <vector>

using namespace std;

std::vector<double> Solve_Kriging_System(const std::vector<std::vector<double> > &LHS_Covariance_Matrix, const std::vector<double> &RHS_Covariance_Matrix){

	


	// Declare RHS_Covariance_Matrix of the library Eigen
	Eigen::VectorXd RHS_Covariance_Matrix_Eigen(RHS_Covariance_Matrix.size(),1);
	// convert std vector RHS Matrix to Vector of the library EIGEN
	for (size_t i = 0; i< RHS_Covariance_Matrix_Eigen.rows(); ++i){
		RHS_Covariance_Matrix_Eigen[i] = RHS_Covariance_Matrix[i];
	}



	// Declare LHS_Covariance_Matrix of the library Eigen
	Eigen::MatrixXd LHS_Covariance_Matrix_Eigen(LHS_Covariance_Matrix.size(),LHS_Covariance_Matrix[0].size());
	// convert std vector RHS Matrix to Vector of the library EIGEN
	for (size_t i = 0; i< LHS_Covariance_Matrix_Eigen.cols(); ++i){
		for (size_t j =0 ; j < LHS_Covariance_Matrix_Eigen.rows(); ++j){
			LHS_Covariance_Matrix_Eigen(i,j) = LHS_Covariance_Matrix[i][j];
		} 
	}

	// Declare Kriging_weights of the library Eigen
	Eigen::VectorXd Kriging_Weights_Eigen(RHS_Covariance_Matrix.size(),1);

	Kriging_Weights_Eigen = LHS_Covariance_Matrix_Eigen.fullPivLu().solve(RHS_Covariance_Matrix_Eigen);
	
	std::vector<double> Kriging_Weights;

	for (size_t i = 0; i < Kriging_Weights_Eigen.rows(); ++i){
		Kriging_Weights.push_back(Kriging_Weights_Eigen(i));
	}

	return Kriging_Weights;

}
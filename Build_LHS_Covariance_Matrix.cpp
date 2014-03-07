/*
Author: Marcel Bassani
*/
# include "Covariance_Point_Point.h"
# include "Covariance_Point_Block.h"
# include "Covariance_Block_Block.h"
# include <vector>

using namespace std;


vector<vector<double> > Build_LHS_Covariance_Matrix(const std::vector<std::vector<double> > &samples, const std::vector<std::vector<double> > &block, const double &range, const double &contribution, const int &kriging_option)
{
	vector<vector<double> > LHS_Covariance_Matrix; // Define the matrix which will receive the covariances
	// Calculate all covariance point-point among the sample points
	for(size_t i = 0; i < samples.size(); ++i)	{    // Calculate Covariance between the sample points
		vector<double> row;// create an empty row
		for (size_t j = 0; j < samples.size(); ++j){
			double covariance_sample_point_sample_point = Covariance_Point_Point(samples[i][0], samples[i][1], samples[i][2], samples[j][0], samples[j][1], samples[j][2], range, contribution);
			row.push_back(covariance_sample_point_sample_point);// Add elemente (column) to the row
		}
		LHS_Covariance_Matrix.push_back(row);// Add the row to the main vector
	}

	// Add the Covariance Point-Block (last Column) to the LHS MAtrix
	for(size_t j = 0; j < samples.size(); ++j){
			double covariance_sample_point_sample_block = Covariance_Point_Block(samples[j][0], samples[j][1], samples[j][2], block, range, contribution);
			LHS_Covariance_Matrix[j].push_back(covariance_sample_point_sample_block);
	}


	// Add the Covariance_Block-Point (last Row) to the LHS_Covariance_Matrix or Covariance Block-Block

	int Numero_De_Blocos = 1;
	vector<double> last_row_lhs_cova_matrix; // create last row of the LHS_Covariance_Matrix
	for(size_t j = 0; j < (samples.size() + Numero_De_Blocos); ++j){
		if (j < samples.size()){
			double covariance_block_point = Covariance_Point_Block(samples[j][0], samples[j][1], samples[j][2], block, range, contribution);
			last_row_lhs_cova_matrix.push_back(covariance_block_point);
		}
		else{
			double covariance_block_block = Covariance_Block_Block(block, block, range, contribution);
			last_row_lhs_cova_matrix.push_back(covariance_block_block);
		}
	}
	LHS_Covariance_Matrix.push_back(last_row_lhs_cova_matrix);


	int size = LHS_Covariance_Matrix[0].size();
	// If kriging option = 0; simple kriging
	// If kriging option = 1; ordinary kriging
	if(kriging_option == 1){
		for (size_t i = 0; i < size; ++i){// add colum to the lines of the Matrix
			double Um = 1.00;
			LHS_Covariance_Matrix[i].push_back(Um);
		}
		//Complete last row of the LHS_Covariance_Matrix

		vector<double> last_row_LHS_cova_matrix_ordinary_kriging;

		for (size_t j = 0; j < LHS_Covariance_Matrix[0].size(); ++ j){
			double Zero = 0.00;
			double Um = 1.00;
			if (j < (LHS_Covariance_Matrix[0].size()-1) ){
				last_row_LHS_cova_matrix_ordinary_kriging.push_back(Um);
			}
			else{
				last_row_LHS_cova_matrix_ordinary_kriging.push_back(Zero);
			}
		}
		LHS_Covariance_Matrix.push_back(last_row_LHS_cova_matrix_ordinary_kriging);


	}




	return LHS_Covariance_Matrix;

}

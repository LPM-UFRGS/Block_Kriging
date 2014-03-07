# include "Covariance_Point_Point.h"
# include "Covariance_Point_Block.h"
# include <vector>

using namespace std;

double Covariance_Point_Block(const double &xi, const double &yi, const double &zi, const vector<vector<double> > &blockj, const double &range, const double &contribution){

	int count = 0;
	double sum_cova_point_point = 0;
	double cova_point_point = 0;
	double cova_point_block = 0;
	
	for(size_t j = 0; j < blockj.size(); ++j){
			cova_point_point = Covariance_Point_Point(xi, yi, zi, blockj[j][0], blockj[j][1], blockj[j][2], range, contribution);
			sum_cova_point_point = sum_cova_point_point + cova_point_point;
			++count;
		}
	cova_point_block = sum_cova_point_point/count;

	return cova_point_block;

}

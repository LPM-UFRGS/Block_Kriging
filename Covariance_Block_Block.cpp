# include "Covariance_Block_Block.h"
# include "Covariance_Point_Point.h"
# include <vector>

using namespace std;

double Covariance_Block_Block(const vector<vector<double> > &blocki, const vector<vector<double> > &blockj, const double &range, const double &contribution )
{
	int count = 0;
	double sum_cova_point_point = 0;
	double cova_point_point = 0;
	double cova_block_block = 0;
	

	for(size_t i = 0; i < blocki.size(); ++i)
	{

		for(size_t j = 0; j < blockj.size(); ++j)
		{

			cova_point_point = Covariance_Point_Point(blocki[i][0], blocki[i][1],blocki[i][2], blockj[j][0], blockj[j][1], blockj[j][2], range, contribution);
			sum_cova_point_point = sum_cova_point_point + cova_point_point;
			++count;
		}
	
	}

	cova_block_block = sum_cova_point_point/count;

	return cova_block_block;
	

}
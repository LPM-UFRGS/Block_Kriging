#ifndef SOLVE_KRIGING_SYSTEM_H
#define SOLVE_KRIGING_SYSTEM_H

# include "Eigen\Dense"
# include <vector>

std::vector<double> Solve_Kriging_System(const std::vector<std::vector<double> > &LHS_Covariance_Matrix, const std::vector<double> &RHS_Covariance_Matrix);
	

#endif
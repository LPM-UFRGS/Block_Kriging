/*
 * LPM_UFRGS_Block_Kriging.cpp
 *
 *  Created on: March 10, 2014
 *      Author: Marcel
 */
# include "Covariance_Point_Point.h"
# include "Covariance_Block_Block.h"
# include "Covariance_Point_Block.h"
# include "Build_LHS_Covariance_Matrix.h"
# include "Build_RHS_Covariance_Matrix.h"
# include "Solve_Kriging_System.h"
# include "Calculate_Estimates.h"
# include "LPM_UFRGS_Block_Kriging.h"

# include <geostat/utilities.h>
# include <utils/string_manipulation.h>
# include <grid/utilities.h>
# include <grid/neighbors.h>
# include <geostat/utilities.h>

using namespace std;

LPM_UFRGS_Block_Kriging::LPM_UFRGS_Block_Kriging() {

}

LPM_UFRGS_Block_Kriging::~LPM_UFRGS_Block_Kriging() {

}

Named_interface* LPM_UFRGS_Block_Kriging::create_new_interface( std::string& ) {
	return new LPM_UFRGS_Block_Kriging;
}

bool LPM_UFRGS_Block_Kriging::initialize( const Parameters_handler* parameters,
			   Error_messages_handler* errors ) {

	   // Read grid of name of the samples
	std::string Point_Samples_Grid_Name = parameters->value( "Location_And_Value_Of_The_Point_Samples.grid" );
		errors->report( Point_Samples_Grid_Name.empty(),
		  "Location_And_Value_Of_The_Point_Samples", "No grid selected" );
		// Set the string "Point_Samples_Grid_Name" To the string field of the Object Point_Locations_And_Values (class Geostat_grid). The method get_grid_from_manager sets the string to the correct place
		this->Point_Locations_And_Value = get_grid_from_manager(Point_Samples_Grid_Name);
	
	if (this->Point_Locations_And_Value == 0) {
		errors->report("The grid " + Point_Samples_Grid_Name + " does not exist");
		return false;
	}

	// Read name of the property of the sample grid
	std::string Point_Samples_Value_Name = parameters->value( "Location_And_Value_Of_The_Point_Samples.property" );
		errors->report( Point_Samples_Value_Name.empty(),
		  "Location_And_Value_Of_The_Point_Samples", "No property name specified" );

	this->Point_Sample_Values = this->Point_Locations_And_Value->property(Point_Samples_Value_Name);

	if (this->Point_Sample_Values == 0) {
			errors->report("The property " + Point_Samples_Value_Name + " does not exist");
			return false;
	}

	// Read the property name of the estimates
	Estimate_Name = parameters->value( "Property_Which_Will_Receive_The_Estimates.value" );
		errors->report( Estimate_Name.empty(),
		  "Property_Which_Will_Receive_The_Estimates", "No property name specified" );



	std::string Block_Grid_Name = parameters->value( "Location_Of_The_Block_Sample.value" );
	errors->report( Block_Grid_Name.empty(),
		"Location_Of_The_Block_Sample", "No grid selected" );
	this->Block_Locations = get_grid_from_manager(Block_Grid_Name);

	if (this->Block_Locations == 0) {
		errors->report("The grid " + Block_Grid_Name + " does not exist");
		return false;
	}


	this->Block_Value = String_Op::to_number<double>(parameters->value("Block_Value.value"));

	this->Contribution_Of_The_Variogram = String_Op::to_number<double>(parameters->value("Contribution_Variogram.value"));

	this->Range_Of_The_Variogram = String_Op::to_number<double>(parameters->value("Range_Of_The_Variogram.value"));

	this->Simple_Kriging_Mean = String_Op::to_number<double>(parameters->value("Simple_Kriging_Mean.value"));


	std::string Kriging_Option = parameters->value( "Kriging_Option.value" );
	

	if (Kriging_Option == "Simple Kriging")
		this->Kriging_Option = SIMPLE_KRIGING;
	else
		this->Kriging_Option = ORDINARY_KRIGING;
	

	Grid_continuous_property *Estimate_Pointer = Block_Locations->add_property(Estimate_Name);
	if (Estimate_Pointer == 0){
		Estimate_Pointer = Block_Locations->property(Estimate_Name);
		if(Estimate_Pointer == 0){
			errors->report("Could not create the property" + Estimate_Name);
			return false;
		}
	
	}
	Estimates = Estimate_Pointer;
	
	return true;
}
		

	

	
#define INF -9999

int LPM_UFRGS_Block_Kriging::execute( GsTL_project* proj ) {
 size_t N_block = Block_Locations->size();
 std::vector<std::vector<double> > Block_Sample_Points;
 
 // put the point locations that make the block into a suitable vector of vector
 for (size_t i = 0; i < N_block; ++i) {
	std::vector<double> row;
	double x, y, z;
	x = Block_Locations->xyz_location(Block_Locations->node_id(i)).x();
	row.push_back(x);// fill the first column of the row with X location
	
	y = Block_Locations->xyz_location(Block_Locations->node_id(i)).y();
	row.push_back(y);
	
	z = Block_Locations->xyz_location(Block_Locations->node_id(i)).z();
	row.push_back(z);
	Block_Sample_Points.push_back(row);
	 
 }

size_t N_points = Point_Sample_Values->size();

 std::vector<std::vector<double> > Sample_Points;
 for (size_t i = 0; i < N_points; ++i) {
	 std::vector<double> row;
	 double x, y ,z, data; 
	 if (Point_Sample_Values->is_informed(i)) {
		data = Point_Sample_Values->get_value(i);
		if (data > -90){
			x = Point_Locations_And_Value->xyz_location(Point_Locations_And_Value->node_id(i)).x();
			row.push_back(x);// fill the first column of the row with X location

			y = Point_Locations_And_Value->xyz_location(Point_Locations_And_Value->node_id(i)).y();
			row.push_back(y);// fill the first column of the row with y location

			z = Point_Locations_And_Value->xyz_location(Point_Locations_And_Value->node_id(i)).z();
			row.push_back(z);// fill the first column of the row with y location

			row.push_back(data);

			Sample_Points.push_back(row);
		
		}

	 } else {
		 data = INF;
	 }
 }

 vector<vector<double> > LHS_Covariance_Matrix = Build_LHS_Covariance_Matrix(Sample_Points, Block_Sample_Points, Range_Of_The_Variogram, Contribution_Of_The_Variogram, Kriging_Option);

 for (size_t i = 0; i < Block_Sample_Points.size(); ++i){
	
		vector <double> RHS_Covariance_Matrix = Build_RHS_Covariance_Matrix(Sample_Points, Block_Sample_Points, Block_Sample_Points[i][0], Block_Sample_Points[i][1], Block_Sample_Points[i][2], Range_Of_The_Variogram, Contribution_Of_The_Variogram, Kriging_Option);
		
		vector <double> Kriging_Weights = Solve_Kriging_System(LHS_Covariance_Matrix, RHS_Covariance_Matrix);

		double estimate = Calculate_Estimates(Sample_Points, Block_Value, Kriging_Weights, Kriging_Option, Simple_Kriging_Mean);
		
		Estimates->set_value(estimate, i);
 }









  return true;

}

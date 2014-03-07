#ifndef __LPM_UFRGS_BLOCK_KRIGING_H
#define __LPM_UFRGS_BLOCK_KRIGING_H


#include "common.h"
#include <geostat/geostat_algo.h>
#include <grid/geostat_grid.h>
#include <grid/grid_property.h>
#include <grid/grid_region.h>
#include <grid/neighborhood.h>
#include <utils/error_messages_handler.h>
#include <appli/project.h>
#include <geostat/parameters_handler.h>

enum {
	SIMPLE_KRIGING = 0,
	ORDINARY_KRIGING = 1
};

class LPM_UFRGS_Block_Kriging : public Geostat_algo {
public:
	LPM_UFRGS_Block_Kriging();
	virtual ~LPM_UFRGS_Block_Kriging();

	  virtual bool initialize( const Parameters_handler* parameters,
				   Error_messages_handler* errors );
	  virtual int execute( GsTL_project* proj=0 );
	  virtual std::string name() const { return "LPM_UFRGS_Block_Kriging"; }

	 public:
	  static Named_interface* create_new_interface( std::string& );

private :/*need files below*/
	Geostat_grid *Point_Locations_And_Value;
	Geostat_grid *Block_Locations;
	double Block_Value, Contribution_Of_The_Variogram, Range_Of_The_Variogram;
	int Kriging_Option;
	double Simple_Kriging_Mean;
	Grid_continuous_property *Point_Sample_Values;
	Grid_continuous_property *Estimates;

	std::string Estimate_Name;

};

#endif /* GEOBODY_H_ */

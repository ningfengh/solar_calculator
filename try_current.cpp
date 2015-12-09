#include <iostream>
#include <string>
#include <fstream>
#include "EQE.h"

int main (void)
{
	EQE my_calculation("./slab/slab_aSi");
	
	ofstream myfile("Power_tilt.txt");
	vector<double> hour_vector;
	vector<double> power;
	for (double tilt = 0; tilt <= 100 ; tilt+=5)
	{
		my_calculation.set_tilt(tilt);
		hour_vector.clear();
		power.clear();		
		for (double hour = 5; hour <= 19; hour+=0.2)
		{	
			my_calculation.set_time(2015,12,1,hour);
			hour_vector.push_back(hour);
			power.push_back(my_calculation.get_direct_power());
		}
		double int_power = 0;		
		for (int i = 0; i < hour_vector.size()-1; i ++){
			int_power+=(power[i]+power[i+1])*(hour_vector[i+1]-hour_vector[i])/2.0;
		}
		myfile<<tilt<<" "<<int_power<<endl;
	}
	myfile.close();

	return 1;
		
}

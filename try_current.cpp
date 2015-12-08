#include <iostream>
#include <string>
#include <fstream>
#include "EQE.h"

int main (void)
{
	EQE my_calculation("./EQE_O4_aSi/O4_aSi");
	
	ofstream myfile("Power.txt");

	for (double tilt = 0; tilt <= 100 ; tilt+=5)
	{
	my_calculation.set_tilt(tilt);
	for (double hour = 5; hour <= 19; hour+=0.2)
	{	
		my_calculation.set_time(2015,12,1,hour);
		myfile<<my_calculation.get_direct_power()<<" ";
	}
	myfile<<endl;
	}
	myfile.close();

	return 1;
		
}

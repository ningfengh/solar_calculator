#include <iostream>
#include <string>
#include <fstream>
#include "SMARTS.hpp"
using namespace std;
void GetDate(const int &N, int &M, int &D){
	int accu_m[] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
	M = 0;
	while (N>accu_m[M]) M++;
	D = N-accu_m[M-1];	
}

int main (void)
{


	SMARTS my_cal;
	double sun_zenith, sun_azimuth;
	double theta, phi;
	my_cal.set_tilt(0);
	for (double time = 12; time<=16; time+=1)
	{
		my_cal.set_time(2015, 6 , 21 , time);
		my_cal.get_power("spectra_tilt_0_time_"+to_string((int)time)+".txt");
		my_cal.get_sun_position(sun_zenith, sun_azimuth);
		my_cal.get_incident_angle(theta, phi);	
		cout<<time<<" "<<sun_zenith<<" "<<sun_azimuth<<" "<<theta<<" "<<phi<<endl;
	}	
/*
	for (double time = 0; time < 24; time+=0.01) {

		my_cal.set_time(2015, 6 , 21 , time);
		my_cal.get_power();
		my_cal.get_sun_position(sun_zenith, sun_azimuth);
		my_cal.get_incident_angle(theta, phi);	
		cout<<time<<" "<<sun_zenith<<" "<<sun_azimuth<<" "<<theta<<" "<<phi<<endl;
	}
*/
	//EQE my_calculation("./slab/slab_aSi");
	//EQE my_calculation("./EQE_O4_aSi/O4_aSi");
	
	


/*
	my_calculation.set_tilt(90);
	ofstream myfile("Power_year_90_O4.txt");
	double year_power = 0;	
	for (int N = 1; N<=365; N++)
	{
		int M,D;
		GetDate(N,M,D);
		vector<double> hour_vector;
		vector<double> power;		
		for (double hour = 4; hour <= 20; hour+=0.2)
		{	
			my_calculation.set_time(2015,M,D,hour);
			hour_vector.push_back(hour);
			power.push_back(my_calculation.get_direct_power());
		}
		double int_power = 0;		
		
		for (size_t i = 0; i < hour_vector.size()-1; i ++){
			int_power+=(power[i]+power[i+1])*(hour_vector[i+1]-hour_vector[i])/2.0;
		}
		myfile<<N<<"\t"<<int_power<<"\t"<<hour_vector.size()<<endl;
		cout<<M<<"\t"<<D<<"\t"<<int_power<<endl;
		year_power += int_power;
	}

	cout<<"total power = "<<year_power<<endl;

	myfile.close();
*/
	return 1;
		
}

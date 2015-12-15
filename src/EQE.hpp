#ifndef _EQE_
#define _EQE_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "SMARTS.hpp"
#define FACTOR 		8.065544000768418e-4


class EQE{
	std::string name;
	int n_wav,n_theta,n_phi;
	std::vector<double> wavelength;
	std::vector<double> theta;
	std::vector<double> phi;
	std::vector<std::vector<std::vector<double>>> data;
	int symmetry;
	SMARTS smarts_cal;
	double Voc;
	double FF;
	double get_eqe(double,double,double);
public:
	EQE(std::string);
	void set_time(int, int , int , double);
	void set_tilt(double);
	double get_direct_power(void);
};


#endif//_EQE_

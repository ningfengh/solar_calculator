#ifndef _EQE_
#define _EQE_

#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
#include "SMARTS.hpp"
#define FACTOR 		8.065544000768418e-4
using namespace std;

class EQE{
	string name;
	int n_wav,n_theta,n_phi;
	vector<double> wavelength;
	vector<double> theta;
	vector<double> phi;
	vector<vector<vector<double>>> data;
	int symmetry;
	SMARTS smarts_cal;
	double Voc;
	double FF;
	double get_eqe(double,double,double);
public:
	EQE(string);
	void set_time(int, int , int , double);
	void set_tilt(double);
	double get_direct_power(void);
};


#endif//_EQE_

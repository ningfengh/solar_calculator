#ifndef _EQE_
#define _EQE_

#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

class EQE{
	string name;
	int n_wav,n_theta,n_phi;
	vector<double> wavelength;
	vector<double> theta;
	vector<double> phi;
	vector<vector<vector<double>>> data;
	int symmetry;
	
public:
	double get_eqe(double,double,double);
	EQE(string);
};


#endif//_EQE_

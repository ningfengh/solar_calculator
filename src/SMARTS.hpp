#ifndef _SMARTS_
#define _SMARTS_
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#define M_PI           3.14159265358979323846
using namespace std;
const char* const DELIMITER = " ";




class SMARTS {
	friend class EQE;

/****************************************/
/*       SMARTS PARAMETERS              */
	string comment;
	int ISPR;
	double pressure, altitude, height;
	int IATMOS;
	string Atmos;
	int IH2O;
	int IO3;
	int IGAS;
	double CO2;
	int ISPCTR;
	string Aeros;
	int ITURB;
	double Turb;
	int IALBDX;
	int ITILT;
	double IALBDG, tilt, azimuth;
	int min_wav, max_wav;
	double sun_earth_correction;
	double solar_constant;
	int IPRT;
	double step_size;
	int num_variables;
	vector<int> variables;
	int ICIRC;
	int ISCAN;
	int ILLUM;
	int IUV;
	int IMASS;
	int time_zone;
	double longitude;
	double latitude;
	int year;
	int month;
	int day;
	double hour;
	double sun_zenith;
	double sun_azimuth;
	double theta;
	double phi;
	bool sun_light;

/****************************************/


	string filename;
	vector<vector<double>> power;
	vector<double> wavelength;
	void get_input(string);
	void calculate(string);

public:
	SMARTS();
	void set_time(int, int, int, double);
	void get_power(void);
	void set_tilt(double);
};

#endif//_SMARTS_

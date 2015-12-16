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

const char* const DELIMITER = " ";




class SMARTS {
	friend class EQE;

/****************************************/
/*       SMARTS PARAMETERS              */
	std::string comment;
	int ISPR;
	double pressure, altitude, height;
	int IATMOS;
	std::string Atmos;
	int IH2O;
	int IO3;
	int IGAS;
	double CO2;
	int ISPCTR;
	std::string Aeros;
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
	size_t num_variables;
	std::vector<int> variables;
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


	std::string filename;
	std::vector<std::vector<double>> power;
	std::vector<double> wavelength;
	void get_input(std::string);
	void calculate(std::string);

public:
	SMARTS();
	void set_time(int, int, int, double);
	void get_power(void);
	void set_tilt(double);
	void get_sun_position(double&, double&);
	void get_incident_angle(double&, double&);
};

#endif//_SMARTS_

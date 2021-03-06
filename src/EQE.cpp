#include "EQE.hpp"
using namespace std;
/*******************************************************************************************************************/
/*
EQE class reads the EQE data from external files and intepolate it to feed 
the energy output calculation

*/

/* 
The format of EQE data files


In general, the EQE data is a 3-dimensional function of wavelength, phi
and theta. 


file_prefix_input.txt
	contains only one line, representing the symmetry fold of phi, 
	for example, for the hexagonal lattice, this number should be 6

file_prefix_wavelength.txt
	first line is the number of wavelength points
	following lines are the wavelength in units of nanometers

file_prefix_theta.txt
	first line is the number of theta points
	following lines are theta 

file_prefix_phi.txt
	first line is the number of phi points
	following lines are phi

file_prefix_theta_AAA_phi_BBB.txt
	actual wavelength dependent EQE for theta AAA and phi BBB
*/



EQE::EQE(string file_prefix){
	string filename;
	string theta_str;
	string phi_str;

	filename = file_prefix + "_input.txt";
	ifstream ifs(filename);    // C++11 allows directly use of string in ifstream constructor

	if (!ifs.is_open()) {cout<<"Cannot open input file!"<<endl;exit(1);}
	ifs>>symmetry;
	ifs.close();

	
	filename = file_prefix + "_wavelength.txt";
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open wavelength file!"<<endl;exit(1);}
	
	ifs>>n_wav;
	for (int i = 0; i < n_wav; i++){
		double wav;
		ifs>>wav;
		wavelength.push_back(wav);
	}
	ifs.close();

	filename = file_prefix + "_theta.txt";
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open theta file!"<<endl;exit(1);}
	
	ifs>>n_theta;
	for (int i = 0; i < n_theta; i++){
		double theta;
		ifs>>theta;
		this->theta.push_back(theta);
	}
	ifs.close();

	filename = file_prefix + "_phi.txt";
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open phi file!"<<endl;exit(1);}
	
	ifs>>n_phi;
	for (int i = 0; i < n_phi; i++){
		double phi;
		ifs>>phi;
		this->phi.push_back(phi);
	}
	ifs.close();


	for (int i = 0; i < n_phi; i++){
		vector<vector<double>> theta_tmp;		
		for (int j = 0; j < n_theta; j++){
			filename = file_prefix+"_theta_"+to_string((int)theta[j])+"_phi_"+to_string((int)phi[i])+".txt";
			ifs.open(filename);	
			if (!ifs.is_open()) {cout<<"Cannot open EQE file "<<filename<<"!"<<endl;exit(1);}
			vector<double> wav_tmp;
			for (int k = 0; k < n_wav; k++) {
				double eqe;
				ifs>>eqe;
				wav_tmp.push_back(eqe);
			}		
			ifs.close();
			theta_tmp.push_back(wav_tmp);
		}	
		data.push_back(theta_tmp);
	}  
	Voc = 0.90;   // initial value for aSi, can be changed
	FF 	= 0.60;
}

double EQE::get_eqe(double phi, double theta, double wavelength) {

/*
trilinear interpolation of EQE data 
*/

	double c00,c01,c10,c11,c0,c1;
	double xd,yd,zd;
	int x0,x1,y0,y1,z0,z1;

	if (symmetry==-1){
		phi = 0;
	}
	else {	
		phi = fmod(phi,360.0/symmetry);
	}


	if (phi<=this->phi[0]){
		x0 = 0; x1 = 0; xd = 0;	
	}
	else if (phi>=this->phi[this->phi.size()-1]){
		x0 = this->phi.size()-1; x1 = this->phi.size()-1; xd = 1;	
	}
	else {
		x1 = 0;
		while (phi>this->phi[x1]) x1++;
		x0 = x1-1;
		xd = (phi - this->phi[x0])/(this->phi[x1]-this->phi[x0]);
	}

	if (theta<=this->theta[0]){
		y0 = 0; y1 = 0; yd = 0;	
	}
	else if (theta>=this->theta[this->theta.size()-1]){
		y0 = this->theta.size()-1; y1 = this->theta.size()-1; yd = 1;	
	}
	else {
		y1 = 0;
		while (theta>this->theta[y1]) y1++;
		y0 = y1-1;
		yd = (theta - this->theta[y0])/(this->theta[y1]-this->theta[y0]);
	}

	if (wavelength<=this->wavelength[0]){
		z0 = 0; z1 = 0; zd = 0;	
	}
	else if (wavelength>=this->wavelength[this->wavelength.size()-1]){
		z0 = this->wavelength.size()-1; z1 = this->wavelength.size()-1; zd = 1;	
	}
	else {
		z1 = 0;
		while (wavelength>this->wavelength[z1]) z1++;
		z0 = z1-1;
		zd = (wavelength - this->wavelength[z0])/(this->wavelength[z1]-this->wavelength[z0]);
	}	

	c00 = data[x0][y0][z0]*(1.0-xd) + data[x1][y0][z0]*xd;
	c01 = data[x0][y0][z1]*(1.0-xd) + data[x1][y0][z1]*xd;
	c10 = data[x0][y1][z0]*(1.0-xd) + data[x1][y1][z0]*xd;
	c11 = data[x0][y1][z1]*(1.0-xd) + data[x1][y1][z1]*xd;

	c0 = c00*(1.0-yd) + c10*yd;
	c1 = c01*(1.0-yd) + c11*yd;
	
	return c0*(1.0-zd) + c1*zd;
}

void EQE::set_time(int year, int month, int day, double hour){
	smarts_cal.set_time(year,month,day,hour);
	smarts_cal.get_power();
}

double EQE::get_direct_power() {

/*
EQE weighted power output from the solar cell by direct illumination by the sun
trapz numerical integration is used
*/

	if (!smarts_cal.sun_light) return 0;
	else {
		double int_power = 0;
		for (size_t i = 0; i<smarts_cal.wavelength.size()-1;i++){
			
			int_power+= (smarts_cal.power[1][i]+smarts_cal.power[1][i+1])*(smarts_cal.wavelength[i+1]-smarts_cal.wavelength[i])/2.0
				*get_eqe(smarts_cal.phi,smarts_cal.theta,(smarts_cal.wavelength[i]+smarts_cal.wavelength[i+1])/2.0)
				*FACTOR*(smarts_cal.wavelength[i]+smarts_cal.wavelength[i+1])/2.0
				*Voc*FF;
		}
		return int_power;
	}

}

void EQE::set_tilt(double tilt) {
	smarts_cal.set_tilt(tilt);
}


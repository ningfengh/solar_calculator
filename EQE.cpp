#include "EQE.h"




EQE::EQE(string file_prefix){
	char filename[1024];
	strcpy(filename,file_prefix.c_str());
	strcat(filename,"_input.txt");
	ifstream ifs(filename);
	if (!ifs.is_open()) {cout<<"Cannot open input file!"<<endl;exit(1);}
	ifs>>symmetry;
	ifs.close();

	
	strcpy(filename,file_prefix.c_str());
	strcat(filename,"_wavelength.txt");
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open wavelength file!"<<endl;exit(1);}
	int n_wav;
	ifs>>n_wav;
	for (int i = 0; i<n_wav; i++){
		double wav;
		ifs>>wav;
		wavelength.push_back(wav);
	}
	ifs.close();

	strcpy(filename,file_prefix.c_str());
	strcat(filename,"_theta.txt");
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open theta file!"<<endl;exit(1);}
	int n_theta;
	ifs>>n_theta;
	for (int i = 0; i<n_theta; i++){
		double theta;
		ifs>>theta;
		this->theta.push_back(theta);
	}
	ifs.close();

	strcpy(filename,file_prefix.c_str());
	strcat(filename,"_phi.txt");
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open phi file!"<<endl;exit(1);}
	int n_phi;
	ifs>>n_phi;
	for (int i = 0; i<n_phi; i++){
		double phi;
		ifs>>phi;
		this->phi.push_back(phi);
	}
	ifs.close();
	
}

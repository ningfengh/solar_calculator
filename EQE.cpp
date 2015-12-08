#include "EQE.h"




EQE::EQE(string file_prefix){
	char filename[1024];
	char theta_str[1024];
	char phi_str[1024];
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
	
	ifs>>n_wav;
	for (int i = 0; i < n_wav; i++){
		double wav;
		ifs>>wav;
		wavelength.push_back(wav);
	}
	ifs.close();

	strcpy(filename,file_prefix.c_str());
	strcat(filename,"_theta.txt");
	ifs.open(filename);
	if (!ifs.is_open()) {cout<<"Cannot open theta file!"<<endl;exit(1);}
	
	ifs>>n_theta;
	for (int i = 0; i < n_theta; i++){
		double theta;
		ifs>>theta;
		this->theta.push_back(theta);
	}
	ifs.close();

	strcpy(filename,file_prefix.c_str());
	strcat(filename,"_phi.txt");
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
			strcpy(filename, file_prefix.c_str());
			strcat(filename, "_theta_");
			sprintf(theta_str,"%d",(int)theta[j]);
			strcat(filename, theta_str);
			strcat(filename, "_phi_");
			sprintf(phi_str,"%d",(int)phi[i]);
			strcat(filename, phi_str);
			strcat(filename, ".txt");
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
}

double EQE::get_eqe(double phi, double theta, double wavelength) {
	if (symmetry==-1){
		phi = 0;
	}
	else {	
		phi = fmod(phi,360.0/symmetry);
	}
	double xd,yd,zd;
	
		

}

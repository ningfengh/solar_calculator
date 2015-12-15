#include "SMARTS.hpp"

using namespace std;

SMARTS::SMARTS() {
	comment 	= "ASTM_G173_Std_Spectra";
	ISPR 		= 1;
	pressure 	= 1013.25; 
	altitude 	= 0.0; 
	height		= 0.0;
	IATMOS 		= 1;
	Atmos 		= "USSA";
	IH2O 		= 1;
	IO3 		= 1;
	IGAS 		= 1;
	CO2 		= 370.0;
	ISPCTR 		= 1;
	Aeros 		= "S&F_RURAL";
	ITURB 		= 0;
	Turb 		= 0.084;
	IALBDX 		= 38;
	ITILT 		= 1;
	IALBDG 		= 38;
 	tilt 		= 37.0;
	azimuth 	= 180.0;
	min_wav 	= 280;
	max_wav 	= 1000;
	sun_earth_correction = 1.0;
	solar_constant = 1367.0;
	IPRT 		= 2;
	step_size 	= 2;
	
	
	variables.push_back(2);
	variables.push_back(6);
	variables.push_back(7);
	variables.push_back(8);
	variables.push_back(9);
	
	num_variables = variables.size();
	power.resize(num_variables);
	ICIRC 		= 0;
	ISCAN 		= 0;
	ILLUM 		= 0;
	IUV 		= 0;
	IMASS 		= 3;
	time_zone 	= -8;
	longitude 	= -121.0822;
	latitude 	= 38.6858;	
	year 		= 2015;
	month		= 1;
	day			= 1;
	hour		= 12;
}

void SMARTS::get_input(string file_name) {

	filename = file_name;
	ofstream m_file(file_name+".inp.txt");

	m_file<<"'"<<comment<<"'"<<"\t\t!Card 1 Comment"<<endl;
	m_file<<ISPR<<"\t\t\t\t!Card 2 ISPR"<<endl;
	m_file<<pressure<<" "<<altitude<<" "<<height<<"\t\t\t!Card 2a Pressure, altitude, height"<<endl;
	m_file<<IATMOS<<"\t\t\t\t!Card 3 IATMOS"<<endl;
	m_file<<"'"<<Atmos<<"'"<<"\t\t\t\t!Card 3a Atmos"<<endl;
	m_file<<IH2O<<"\t\t\t\t!Card 4 IH2O"<<endl;
	m_file<<IO3<<"\t\t\t\t!Card 5 IO3"<<endl;
	m_file<<IGAS<<"\t\t\t\t!Card 6 IGAS"<<endl;
	m_file<<CO2<<"\t\t\t\t!Card 7 CO2 amount (ppm)"<<endl;
	m_file<<ISPCTR<<"\t\t\t\t!Card 7a ISPCTR"<<endl;
	m_file<<"'"<<Aeros<<"'\t\t\t!Card 8 Aeros (aerosol model)"<<endl;
	m_file<<ITURB<<"\t\t\t\t!Card 9 ITURB"<<endl;
	m_file<<Turb<<"\t\t\t\t!Card 9a Turbidity coeff. (TAU5)"<<endl;
	m_file<<IALBDX<<"\t\t\t\t!Card 10 IALBDX"<<endl;
	m_file<<ITILT<<"\t\t\t\t!Card 10b ITILT"<<endl;
	m_file<<IALBDG<<" "<<tilt<<" "<<azimuth<<"\t\t\t!Card 10c Tilt variables (IALBDG, reciever's tilt & azimuth)"<<endl;
	m_file<<min_wav<<" "<<max_wav<<" "<<sun_earth_correction<<" "<<solar_constant<<"\t\t\t!Card 11 Min & max wavelengths; sun-earth distance correction; solar constant"<<endl;
	m_file<<IPRT<<"\t\t\t\t!Card 12 IPRT"<<endl;
	m_file<<min_wav<<" "<<max_wav<<" "<<step_size<<"\t\t\t!Card 12a Min & max wavelengths to be printedl ideal printing step size"<<endl;
	m_file<<num_variables<<"\t\t\t\t!Card 12b Number of Variables to Print"<<endl;
	for (size_t i=0;i<num_variables;i++) m_file<<variables[i]<<" ";
	m_file<<"\t\t\t!Card 12c Variable codes"<<endl;
	m_file<<ICIRC<<"\t\t\t\t!Card 13 ICIRC bypass here"<<endl;
	m_file<<ISCAN<<"\t\t\t\t!Card 14 ISCAN"<<endl;
	m_file<<ILLUM<<"\t\t\t\t!Card 15 ILLUM"<<endl;
	m_file<<IUV<<"\t\t\t\t!Card 16 IUV"<<endl;
	m_file<<IMASS<<"\t\t\t\t!Card 17 IMASS"<<endl;
	m_file<<year<<" "<<month<<" "<<day<<" "<<hour<<" "<<latitude<<" "<<longitude<<" "<<time_zone<<"\t\t!Card 17a Air mass"<<endl;
	m_file.close();


//  at the same time delete the ext and out files

	remove((file_name+".ext.txt").c_str());
	remove((file_name+".out.txt").c_str());
	remove("dump.txt");
}

void SMARTS::calculate(string executable) {
	if (filename.size()==0) {cout<<"please generate input file first!"<<endl;exit(1);}
	ofstream tmp("tmp.txt");
	tmp<<"N"<<endl;
	tmp<<"."<<endl;
	tmp<<filename<<endl;
	tmp<<"Y"<<endl;
	tmp.close();
//    Execute SMARTS2 software
	int err = system((executable+"<tmp.txt>dump.txt").c_str());
	if (err) {cout<<"Error when executing SMARTS2"<<endl;exit(1);}

	remove("tmp.txt");

	ifstream result(filename+".out.txt");
	if (!result.is_open()) {cout<<"cannot open the result file!"<<endl;exit(1);}
	sun_light = false;
	while (!result.eof())
	{
		char buf[1024];
		result.getline(buf,1024);
		if (strstr(buf,"Zenith Angle")!=NULL)
		{
			int n;
			const char* token[100] = {};
			token[0] = strtok(buf,DELIMITER);
			if (token[0])
			{
				for (n = 1;n<100;n++)
				{
					token[n] = strtok(NULL,DELIMITER);
					if (!token[n]) break;
				}
			}
			sun_zenith = atof(token[4]);
			sun_azimuth = atof(token[9]);
			sun_light = true;
			//cout<<"sun zenith = "<<sun_zenith<<", sun azimuth = "<<sun_azimuth<<endl;
		}
	}	
	if (sun_light) {
		vector <double> surface_normal(3);
		vector <double> sun_vector(3);
		vector <double> surface_north(3);
		vector <double> on_surface(3);	
		surface_normal[0] = sin(tilt*M_PI/180.0)*cos(azimuth*M_PI/180.0);
		surface_normal[1] = sin(tilt*M_PI/180.0)*sin(azimuth*M_PI/180.0);
		surface_normal[2] = cos(tilt*M_PI/180.0);

		sun_vector[0] = sin(sun_zenith*M_PI/180.0)*cos(sun_azimuth*M_PI/180.0);
		sun_vector[1] = sin(sun_zenith*M_PI/180.0)*sin(sun_azimuth*M_PI/180.0);
		sun_vector[2] = cos(sun_zenith*M_PI/180.0);

		double projection = surface_normal[0]*sun_vector[0]+surface_normal[1]*sun_vector[1]+surface_normal[2]*sun_vector[2];
		theta = acos(projection)*180.0/M_PI;
	
		surface_north[0] = cos(tilt*M_PI/180.0);
		surface_north[1] = 0;
		surface_north[2] = sin(tilt*M_PI/180.0);
	
		on_surface[0] = sun_vector[0] - projection*surface_normal[0];
		on_surface[1] = sun_vector[1] - projection*surface_normal[1];
		on_surface[2] = sun_vector[2] - projection*surface_normal[2];

		double on_surface_norm = sqrt(on_surface[0]*on_surface[0]+on_surface[1]*on_surface[1]+on_surface[2]*on_surface[2]);
		double proj_temp = (on_surface[0]*surface_north[0]+on_surface[1]*surface_north[1]+on_surface[2]*surface_north[2])/on_surface_norm;
		if (proj_temp>1) proj_temp = 1;  // to prevent the numerical error which can cause projection to be slightly larger than one
		if (proj_temp<-1) proj_temp = -1;
		phi = acos(proj_temp)*180.0/M_PI;
		if (on_surface[1]<0)
			phi = 360-phi;

		//cout<<"theta = "<<theta<<", phi = "<<phi<<endl;	
	}
	result.close();
}

void SMARTS::get_power(void){
	

	get_input("try");
	calculate("./smarts295");	


	if (sun_light){
		char file_name[1024];
		strcpy(file_name,filename.c_str());
		strcat(file_name,".ext.txt");
		ifstream result(file_name);	

		double wav;
		char buf[1024];
		result.getline(buf,1024);
		wavelength.clear();
		for (size_t i = 0; i < num_variables; i++) {
			power[i].clear();
		}
		while (result>>wav)
		{
			wavelength.push_back(wav);
			for (size_t i = 0;i < num_variables;i++){
				double tmp; result>>tmp;
				power[i].push_back(tmp);	
			}
		}
	
		for (size_t i = 0 ;i<num_variables;i++){
			double int_power = 0;
			for (size_t j = 0; j<wavelength.size()-1;j++){
				int_power+= (power[i][j]+power[i][j+1])*(wavelength[j+1]-wavelength[j])/2.0;
			}
			//cout<<int_power<<endl;
		}
	}
}

void SMARTS::set_time(int year, int month, int day, double hour){
	this->year 	= year;
	this->month = month;
	this->day 	= day;
	this->hour 	= hour;
}

void SMARTS::set_tilt(double tilt) {
	this->tilt = tilt;
}

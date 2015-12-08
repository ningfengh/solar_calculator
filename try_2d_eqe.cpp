#include <iostream>
#include <string>
#include <fstream>
#include "SMARTS.h"
#include "EQE.h"

int main (void)
{
	SMARTS smarts_input;
	EQE my_calculation("./EQE_O4_aSi/O4_aSi");
	double phi = 0;
	ofstream myout("my_eqe_fine.txt");		
	for (double theta = 30; theta<=30; theta+=0.1){
		for (double wav = 400; wav<=690; wav+=0.10) {
			myout<<wav<<" "<<my_calculation.get_eqe(phi,theta,wav)<<endl;
		}
		
	}	
	myout.close();

	myout.open("my_eqe.txt");		
	for (double theta = 35; theta<=35; theta+=0.1){
		for (double wav = 400; wav<=690; wav+=10) {
			myout<<wav<<" "<<my_calculation.get_eqe(phi,theta,wav)<<endl;
		}
		
	}	
	myout.close();


	return 1;
		
}

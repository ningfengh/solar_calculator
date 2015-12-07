#include <iostream>
#include <string>
#include "SMARTS.h"
#include "EQE.h"

int main (void)
{
	SMARTS smarts_input;
	EQE my_calculation("./EQE_O4_aSi/O4_aSi");
	smarts_input.set_time(2015,12,31,9.5);
	smarts_input.get_input("try");
	smarts_input.calculate("./smarts295");
	smarts_input.get_power();
	return 1;
		
}

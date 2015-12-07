#include <iostream>
#include <string>
#include "SMARTS.h"

int main (void)
{
	SMARTS smarts_input;
	//smarts_input.set_time(2015,12,31,12.5);
	smarts_input.get_input("try");
	smarts_input.calculate("./smarts295");
	return 1;
		
}

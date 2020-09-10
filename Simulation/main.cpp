#include <iostream>

#include "TestBattery.h"

int main()
{
	std::cout << "Nothing here bruv" << std::endl;

	if (true)
	{
		TestBattery tests;
		tests.RunTests();
	}
	else
	{
		std::cout << "unreachable" << std::endl;
	}

	return 0;
}

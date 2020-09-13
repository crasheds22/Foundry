#include <iostream>

#include "Tests/TestBattery.h"

int main()
{
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

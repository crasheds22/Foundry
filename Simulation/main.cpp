#include <iostream>

#include "Tests/TestBattery.h"
#include "Theatre.h"

int main()
{
	//TestBattery tester;
	//tester.RunTests();

	Theatre* theatre = &Theatre::Instance();

	theatre->PreShow();

	theatre->PlayShow();

	theatre->EndShow();

	return 0;
}

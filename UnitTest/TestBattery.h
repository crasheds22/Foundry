#pragma once
#include "UnitTest.h"
#include <list>
#include <iostream>

class TestBattery
{
public:
	TestBattery();

	bool RunTests();

private:
	std::list<UnitTest> TestList {};
};

TestBattery::TestBattery()
{
	//Create new tests here, add to TestList
}

bool TestBattery::RunTests()
{
	bool allPassed = true;

	for (auto& ut : TestList)
	{
		if (ut.Test())
		{
			//Replace this with a call to the log project later
			std::cout << "PASSED: " << ut.TestName() << std::endl;
		}
		else
		{
			std::cout << "FAILED: " << ut.TestName() << std::endl;
			allPassed = false;
		}
	}

	return allPassed;
}

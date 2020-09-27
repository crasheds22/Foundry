#pragma once
#include "UnitTest.h"
#include <list>
#include <iostream>

#include "GraphicsTest.h"
#include "ComponentTest.h"
#include "SystemTest.h"
#include "ColliderTest.h"
#include "ManagerTest.h"
#include "ResourceManagerTest.h"

class TestBattery
{
public:
	TestBattery();
	~TestBattery();

	bool RunTests();

private:
	std::list<UnitTest*> TestList {};
};

TestBattery::TestBattery()
{
	//Create new tests here, add to TestList
	TestList.push_back(new GraphicsTest());
	TestList.push_back(new ComponentTest());
	TestList.push_back(new SystemTest());
	TestList.push_back(new ColliderTest());
	TestList.push_back(new ManagerTest());
	TestList.push_back(new ResourceManagerTest());
}

TestBattery::~TestBattery()
{
	std::list<UnitTest*>::iterator it = TestList.begin();

	while (it != TestList.end())
	{
		delete (*it);
		TestList.remove(*(it++));
	}
}

bool TestBattery::RunTests()
{
	bool allPassed = true;

	for (auto& ut : TestList)
	{
		if (ut->Test())
		{
			//Replace this with a call to the log project later
			std::cout << "PASSED: " << ut->TestName() << std::endl;
		}
		else
		{
			std::cout << "FAILED: " << ut->TestName() << std::endl;
			allPassed = false;
		}
	}

	return allPassed;
}

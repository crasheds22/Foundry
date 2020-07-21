#pragma once
#include <string>

class UnitTest
{
public:
	UnitTest(std::string Name) { this->Name = Name; }
	virtual ~UnitTest() { };

	virtual bool Test();

	std::string TestName() const { return Name; }

private:
	std::string Name;
};

#pragma once
#include "UnitTest.h"

#include <iostream>

#include "Resource/Manager.h"

class Integer
{
public:
    Integer(int i);

    int Int() const;

private:
    int mInt;
};

class ManagerTest :
    public UnitTest
{
public:
    ManagerTest() : UnitTest("ManagerTests") {};

    bool Test() override;

private:
    bool ManagerForInts();
    bool ManagerForIntegers();

};


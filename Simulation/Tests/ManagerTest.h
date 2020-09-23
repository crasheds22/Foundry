#pragma once
#include "UnitTest.h"

#include <iostream>

#include "Resource/Manager.h"

class ManagerTest :
    public UnitTest
{
public:
    ManagerTest() : UnitTest("ManagerTests") {};

    bool Test() override;

private:
    bool ManagerForInts();

};


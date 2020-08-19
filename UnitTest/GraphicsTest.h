#pragma once
#include "UnitTest.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GraphicsTest :
    public UnitTest
{
public:
    GraphicsTest() : UnitTest("Graphics Test") { };

    bool Test() override;
    
private:

};


#pragma once
#include "UnitTest.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

class GraphicsTest :
    public UnitTest
{
public:
    GraphicsTest() : UnitTest("Graphics Test") { };

    bool Test() override;
    
private:
    bool HelloWindow();
    bool HelloTriangle();
    bool UsingShaders();
    bool Textures();
};


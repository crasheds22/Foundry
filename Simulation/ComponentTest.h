#pragma once

#include "UnitTest.h"

#include "../Graphics/Graphics.h"

#include "../Simulation/com_Shader.h"

class ComponentTest
	: public UnitTest
{
public:
	ComponentTest() : UnitTest("Component Tests") {};

	bool Test() override;

	float SCR_WIDTH = 800.0f;
	float SCR_HEIGHT = 500.0f;



private:
	bool ShaderComponent();
	bool TextureComponent();
	bool ModelComponent();
	bool CameraComponent();
};


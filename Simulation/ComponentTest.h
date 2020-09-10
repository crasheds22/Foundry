#pragma once

#include "UnitTest.h"

#include "../Graphics/Graphics.h"
#include "../Graphics/Texture.h"

#include "com_Shader.h"
#include "com_Texture.h"

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


#pragma once

#include "UnitTest.h"

#include "Graphics.h"
#include "Texture.h"

#include "com_Shader.h"
#include "com_Texture.h"
#include "com_Camera.h"
#include "com_Model.h"

class ComponentTest
	: public UnitTest
{
public:
	ComponentTest() : UnitTest("Component Tests") {};

	bool Test() override;

	float SCR_WIDTH = 800.0f;
	float SCR_HEIGHT = 500.0f;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bool FirstMouse = true;

	float lastX = 0.0f;
	float lastY = 0.0f;

	Component::com_Camera camera;

private:
	bool ShaderComponent();
	bool TextureComponent();
	bool ModelComponent();
	bool CameraComponent();
};


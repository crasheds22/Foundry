#pragma once

#include "UnitTest.h"

#include "Graphics.h"

#include "sys_Render.h"
#include "com_Model.h"
#include "com_Shader.h"
#include "com_Transform.h"
#include "com_Camera.h"

class SystemTest
	: public UnitTest
{
public:
	SystemTest();

	bool Test() override;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bool FirstMouse = true;

	float lastX = 0.0f;
	float lastY = 0.0f;

	Component::com_Camera camera;

	static void ScrollCallback(GLFWwindow* window, double xOff, double yOff);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ProcessInput(GLFWwindow* window, Component::com_Camera* camera, float dt);

private:
	bool RenderSystem();

};

#pragma once

#include "UnitTest.h"

#include "Graphics/Graphics.h"

#include "Props.h"
#include "Actions.h"

#include "Systems/sys_Render.h"

#include "Components/com_Model.h"
#include "Components/com_Transform.h"
#include "Components/com_Shader.h"
#include "Components/com_Camera.h"

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

	Props* ref = nullptr;

	static void ScrollCallback(GLFWwindow* window, double xOff, double yOff);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	void ProcessInput(Graphics* context);
	static void ProcessInput(GLFWwindow* window, Component::com_Camera* camera, float dt);

	void ProcessMouse();

private:
	bool RenderSystem();
	bool ControlSystem();

};


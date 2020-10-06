#pragma once

#include "UnitTest.h"

#include <iostream>
#include <glm/vec3.hpp>

#include "Components/Components.h"

#include "Systems/sys_Render.h"
#include "Systems/sys_PlayerControl.h"
#include "Systems/sys_Physics.h"

class PhysicsTest : public UnitTest {
public:
	PhysicsTest();

	bool Test() override;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bool FirstMouse = true;

	float lastX = 0.0f;
	float lastY = 0.0f;

	Component::com_Camera camera;

	Resource::ResourceManager* ResMgr = &Resource::ResourceManager::Instance();

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
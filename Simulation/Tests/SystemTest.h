#pragma once

#include "UnitTest.h"

#include "Graphics/Graphics.h"

#include "Resource/ResourceManager.h"

#include "Props.h"
#include "Actions.h"

#include "Systems/sys_Render.h"
#include "Systems/sys_PlayerControl.h"
#include "Systems/sys_Physics.h"

#include "Components/com_Transform.h"
#include "Components/com_Camera.h"
#include "Components/com_Player.h"
#include "Components/com_Render.h"
#include "Components/com_Physics.h"

#include "Components/Collider.h"

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
	bool PhysicsSystem();

};


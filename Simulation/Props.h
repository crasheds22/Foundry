#pragma once

#include <glad/glad.h>

#include <map>

#include "../Graphics/Graphics.h"

#include "com_Camera.h"

enum class Action { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Props
{
public:
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ScrollWheelCallback(GLFWwindow* window, double xOff, double yOff);
	static void ResizeCallback(GLFWwindow* window, int width, int height);

	static void CalcDeltaTime();
	static double DeltaTime();

	static Component::Camera* GetActiveCamera();
	static void SetActiveCamera(Component::Camera* cam);

	static bool KeyDown(Action key);
	static bool KeyHeld(Action key);
	static bool KeyUp(Action key);

private:
	Props() {};
	Props(const Props& p) {};
	~Props() {};

	static double mCurrentTime;
	static double mLastFrame;
	static double mDeltaTime;

	static Component::Camera* mActiveCamera;

	static std::map<int, bool> mKeyDown;
	static std::map<int, bool> mKeyUp;

	static std::map<Action, int> mKeyBind;
};


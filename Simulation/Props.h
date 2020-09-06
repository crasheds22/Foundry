#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

#include "../Graphics/Graphics.h"

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

private:
	Props() {};
	Props(const Props& p) {};
	~Props() {};

	static double mCurrentTime;
	static double mLastFrame;
	static double mDeltaTime;
};


#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

class Props
{
public:
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ScrollWheelCallback(GLFWwindow* window, double xOff, double yOff);

private:
	Props() {};
	Props(const Props& p) {};
	~Props() {};


};


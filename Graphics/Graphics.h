#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class _Graphics
{
public:
	static void InitializeGLFW();
	static void InitializaGLAD();
	static GLFWwindow* CreateWindow(int width, int height, std::string title);
	static void MakeWindowCurrent(GLFWwindow* window);

	static void SetResizeCallback(GLFWwindow* window, void(*resize)(GLFWwindow*, int, int));

	static bool ShouldWindowClose(GLFWwindow* window);
	static void SetWindowShouldClose(GLFWwindow* window);

	static void Clear(float r = 0.0f, float b = 0.0f, float g = 0.0f, float a = 0.0f);

	static void SwapBuffers(GLFWwindow* window);
	static void PollForEvents();

	static void Terminate();
private:
	_Graphics() { };
	_Graphics(const _Graphics& G) { };
	~_Graphics() { };
};

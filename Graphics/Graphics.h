#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Graphics
{
public:
	static void InitializeGLFW();
	static void InitializeGlad();

	static GLFWwindow* CreateWindow(int width, int height, std::string title);

	static void MakeContextCurrent(GLFWwindow* window);

	static void AssignFrameBufferSizeCallback(GLFWwindow* window, void(*func)(GLFWwindow*, int, int));

	static bool ShouldWindowClose(GLFWwindow* window);
	static void SetWindowShouldClose(GLFWwindow* window);

	static void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

	static void SwapBuffers(GLFWwindow* window);

	static void PollForEvents();

	static void TerminateGLFW();

private:
	Graphics() { };
};

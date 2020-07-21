#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cassert>

class Graphics
{
public:
	static void InitializeGLFW()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	static void InitializeGlad()
	{
		assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && "Glad failed to load");
	}

	static GLFWwindow* CreateWindow(int width, int height, std::string title)
	{
		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		assert(window != NULL && "GLFW failed to create window");

		return window;
	}

	static void MakeContextCurrent(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
	}

	static void AssignFrameBufferSizeCallback(GLFWwindow* window, void(*func)(GLFWwindow*, int, int))
	{
		glfwSetFramebufferSizeCallback(window, func);
	}

	static bool ShouldWindowClose(GLFWwindow* window)
	{
		return glfwWindowShouldClose(window);
	}

	static void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	static void SwapBuffers(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}

	static void PollForEvents()
	{
		glfwPollEvents();
	}

	static void TerminateGLFW()
	{
		glfwTerminate();
	}

private:
	Graphics() { };
};

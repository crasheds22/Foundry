#include "Graphics.h"

#include <cassert>

void Graphics::InitializeGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Graphics::InitializeGlad()
{
	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && "Glad failed to load");
}

GLFWwindow* Graphics::CreateWindow(int width, int height, std::string title)
{
	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	assert(window != NULL && "GLFW failed to create window");

	return window;
}

void Graphics::MakeContextCurrent(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

void Graphics::AssignFrameBufferSizeCallback(GLFWwindow* window, void(*func)(GLFWwindow*, int, int))
{
	glfwSetFramebufferSizeCallback(window, func);
}

void Graphics::SetWindowShouldClose(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, true);
}

bool Graphics::ShouldWindowClose(GLFWwindow* window)
{
	return glfwWindowShouldClose(window);
}

void Graphics::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::SwapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Graphics::PollForEvents()
{
	glfwPollEvents();
}

void Graphics::TerminateGLFW()
{
	glfwTerminate();
}

#include "Graphics.h"

#include <iostream>
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

void Graphics::GenerateVertexArrays(unsigned int* arrays, int n)
{
	glGenVertexArrays(n, arrays);
}

void Graphics::GenerateBuffers(unsigned int* buffers, int n)
{
	glGenBuffers(n, buffers);
}

void Graphics::BindArray(unsigned int array)
{
	glBindVertexArray(array);
}

void Graphics::BindBuffer(unsigned int buffer, GLsizeiptr size, void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Graphics::VertexAttribPointer(unsigned int vertIndex, int size, GLenum type, GLsizei stride, const void* offset)
{
	glVertexAttribPointer(vertIndex, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(vertIndex);
}

void Graphics::DrawArrays(GLenum mode, int first, GLsizei count)
{
	glDrawArrays(mode, first, count);
}

void Graphics::DeleteArrays(unsigned int* arrays, int n)
{
	glDeleteVertexArrays(n, arrays);
}

void Graphics::DeleteBuffers(unsigned int* buffers, int n)
{
	glDeleteBuffers(n, buffers);
}

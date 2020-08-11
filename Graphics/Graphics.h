#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

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

	static void GenerateVertexArrays(unsigned int* arrays, int n = 1);
	static void GenerateBuffers(unsigned int* buffers, int n = 1);

	static void BindArray(unsigned int array);
	static void BindBuffer(unsigned int buffer, GLsizeiptr size, void* data);

	static void VertexAttribPointer(unsigned int vertIndex, int size, GLenum type, GLsizei stride, const void* offset);

	static void DrawArrays(GLenum mode, int first, GLsizei count);

	static void DeleteArrays(unsigned int* arrays, int n);
	static void DeleteBuffers(unsigned int* buffers, int n);

private:
	Graphics() { };
};

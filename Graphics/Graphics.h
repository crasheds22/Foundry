#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class _Graphics
{
public:
	enum class BufferType { ELEMENT, ARRAY };

	enum class Shape { TRIANGLES };

	enum class DataType { UNSIGNED_INT, FLOAT };

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

	static void GenerateVertexArrays(unsigned int& ID, int n = 1);
	static void GenerateBuffer(unsigned int& ID, int n = 1);

	static void BindArray(unsigned int ID);
	static void BindBuffer(BufferType type, unsigned int ID, GLsizeiptr sizeptr, const void* data);
	static void VertexAttirbutePointer(int index, int size, GLsizei stride, const void* offset);

	static void UnbindBuffer(BufferType type);
	static void UnbindArray();

	static void DrawElements(Shape shapes, GLsizei count, DataType type, const void* indices);

	static void DeleteBuffers(unsigned int& ID, int n);
	static void DeleteArrays(unsigned int& ID, int n);

	static void DeleteProgram(unsigned int ID);
private:
	_Graphics() { };
	_Graphics(const _Graphics& G) { };
	~_Graphics() { };

	static GLenum Deserialise(BufferType type);
	static GLenum Deserialise(Shape type);
	static GLenum Deserialise(DataType type);
};

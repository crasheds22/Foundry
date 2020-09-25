#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Graphics
{
public:
	enum class BufferType { ELEMENT, ARRAY };

	enum class Shape { TRIANGLES };

	enum class DataType { UNSIGNED_INT, FLOAT };

	enum class Unit { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

	enum class Capability { DEPTH };

	Graphics() {};
	Graphics(int width, int height, std::string title);
	~Graphics();

	void InitializeGLAD();

	GLFWwindow* Window() const;

	void MakeWindowCurrent();

	void SetResizeCallback(void(*resize)(GLFWwindow*, int, int));
	void SetMouseButtonCallback(void(*mouseBtn)(GLFWwindow*, int, int, int));
	void SetCursorCallback(void(*cursor)(GLFWwindow*, double, double));
	void SetScrollCallback(void(*scroll)(GLFWwindow*, double, double));
	void SetKeyboardCallback(void(*keys)(GLFWwindow*, int, int, int, int));

	void StickyKeys();
	void CaptureMouse();

	bool ShouldWindowClose();
	void SetWindowShouldClose();
	static void SetWindowShouldClose(GLFWwindow* window);

	void Clear(float r = 0.0f, float b = 0.0f, float g = 0.0f, float a = 0.0f);

	void SwapBuffers();
	void PollForEvents();

	bool KeyPressed(int key);
	void MousePos(double& x, double& y);

	void Terminate();

	static void GenerateVertexArrays(unsigned int& ID, int n = 1);
	static void GenerateBuffer(unsigned int& ID, int n = 1);

	static void BindArray(unsigned int ID);
	static void BindBuffer(BufferType type, unsigned int ID);
	static void BindBufferAndData(BufferType type, unsigned int ID, GLsizeiptr sizeptr, const void* data);
	static void VertexAttirbutePointer(int index, int size, GLsizei stride, const void* offset);

	static void UnbindBuffer(BufferType type);
	static void UnbindArray();

	static void DrawElements(Shape shapes, GLsizei count, DataType type, const void* indices);
	static void DrawArrays(Shape shapes, int first, GLsizei count);

	static void DeleteBuffers(unsigned int& ID, int n);
	static void DeleteArrays(unsigned int& ID, int n);

	static void DeleteProgram(unsigned int ID);

	static void BindTextureOnUnit(Unit unit, unsigned int ID);

	static void SetWindowUserPointer(GLFWwindow* window, void* pointer);

	static void Enable(Capability cap);
	static void Disable(Capability cap);

	static float GetTime();

	double ScreenWidth() const;
	double ScreenHeight() const;

	float AspectRatio() const;

private:
	void InitializeGLFW();

	static GLenum Deserialise(BufferType type);
	static GLenum Deserialise(Shape type);
	static GLenum Deserialise(DataType type);
	static GLenum Deserialise(Unit unit);
	static GLenum Deserialise(Capability cap);

	double mScreenWidth;
	double mScreenHeight;

	GLFWwindow* mWindow;
};

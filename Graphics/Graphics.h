#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

enum class eTarget
{
	ArrayBuffer,
	ElementArrayBuffer,

};

static GLenum ToGLEnum(eTarget target)
{
	switch (target)
	{
	case eTarget::ArrayBuffer:
		return GL_ARRAY_BUFFER;
	case eTarget::ElementArrayBuffer:
		return GL_ELEMENT_ARRAY_BUFFER;
	default:
		throw std::invalid_argument("Exhaustive case : target");
	}
}

enum class eMode
{
	ArrayBuffer,
	ElementArrayBuffer,
	Traingles,

};

static GLenum ToGLEnum(eMode mode)
{
	switch (mode)
	{
	case eMode::ArrayBuffer:
		return GL_ARRAY_BUFFER;
	case eMode::ElementArrayBuffer:
		return GL_ELEMENT_ARRAY_BUFFER;
	case eMode::Traingles:
		return GL_TRIANGLES;
	default:
		throw std::invalid_argument("Exhaustive case : mode");
	}
}

enum class eUsage
{
	StaticDraw,

};

static GLenum ToGLEnum(eUsage use)
{
	switch (use)
	{
	case eUsage::StaticDraw:
		return GL_STATIC_DRAW;
	default:
		throw std::invalid_argument("Exhaustive case : usage");
	}
}

enum class eType
{
	Float,
	Unsigned_int,

};

static GLenum ToGLEnum(eType type)
{
	switch (type)
	{
	case eType::Float:
		return GL_FLOAT;
	case eType::Unsigned_int:
		return GL_UNSIGNED_INT;
	default:
		throw std::invalid_argument("Exhaustive case : type");
	}
}

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

	static int VertexShader(const char* source);
	static int FragmentShader(const char* source);
	static int LinkShaders(int vertex, int frag);

	static void GenerateArrays(GLuint *arrays, int n = 1);
	static void GenerateBuffers(GLuint* buffers, int n = 1);
	static void BindArray(GLuint array);

	static void BindBuffer(eTarget target, int buffer);
	static void BufferData(eMode mode, GLsizeiptr size, void* data, eUsage use);

	static void VertexAtttribPointer(int index, int size, eType type, bool normalized, std::size_t stride, void* pointer);
	static void EnableVertexAttribArray(int index = 0);
	static void DisableVertexAttribArray(int index = 0);

	static void UseShaderProgram(int shader);

	static void DrawElements(eMode mode, std::size_t count, eType type, void* indices);

	static void DeleteArray(GLuint* arrays, int n = 1);
	static void DeleteBuffers(GLuint* buffers, int n = 1);
	static void DeleteShaderProgram(int shader);

private:
	Graphics() { };
};

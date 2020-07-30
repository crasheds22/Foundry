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

int Graphics::VertexShader(const char* source)
{
	int vShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vShader, 1, &source, NULL);
	glCompileShader(vShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "Error: Vertex compilation failed\n" << infoLog << std::endl;
		return 0;
	}

	return vShader;
}

int Graphics::FragmentShader(const char* source)
{
	int fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fShader, 1, &source, NULL);
	glCompileShader(fShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fShader, 512, NULL, infoLog);
		std::cout << "Error: Fragment shader compilation failed\n" << infoLog << std::endl;
		return 0;
	}

	return fShader;
}

int Graphics::LinkShaders(int vertex, int frag)
{
	int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, frag);

	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error: shader program linking failed\n" << infoLog << std::endl;
		return 0;
	}

	glDeleteShader(vertex);
	glDeleteShader(frag);

	return shaderProgram;
}

void Graphics::GenerateArrays(GLuint* arrays, int n)
{
	glGenVertexArrays(n, arrays);
}

void Graphics::GenerateBuffers(GLuint* buffers, int n)
{
	glGenBuffers(n, buffers);
}

void Graphics::BindArray(GLuint array)
{
	glBindVertexArray(array);
}

void Graphics::BindBuffer(eTarget target, int buffer)
{
	glBindBuffer(ToGLEnum(target), buffer);
}

void Graphics::BufferData(eMode mode, GLsizeiptr size, void* data, eUsage use)
{
	glBufferData(ToGLEnum(mode), size, data, ToGLEnum(use));
}

void Graphics::VertexAtttribPointer(int index, int size, eType type, bool normalized, std::size_t stride, void* pointer)
{
	glVertexAttribPointer(index, size, ToGLEnum(type), normalized, stride, pointer);
}

void Graphics::EnableVertexAttribArray(int index)
{
	glEnableVertexAttribArray(index);
}

void Graphics::DisableVertexAttribArray(int index)
{
	glDisableVertexAttribArray(index);
}

void Graphics::UseShaderProgram(int shader)
{
	glUseProgram(shader);
}

void Graphics::DrawElements(eMode mode, std::size_t count, eType type, void* indices)
{
	glDrawElements(ToGLEnum(mode), count, ToGLEnum(type), indices);
}

void Graphics::DeleteArray(GLuint* arrays, int n)
{
	glDeleteVertexArrays(n, arrays);
}

void Graphics::DeleteBuffers(GLuint* buffers, int n)
{
	glDeleteBuffers(n, buffers);
}

void Graphics::DeleteShaderProgram(int shader)
{
	glDeleteProgram(shader);
}

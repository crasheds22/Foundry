#include "Graphics.h"

void _Graphics::InitializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void _Graphics::InitializaGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        std::exit(1);
    }
}

GLFWwindow* _Graphics::CreateWindow(int width, int height, std::string title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        std::exit(1);
    }
    return window;
}

void _Graphics::MakeWindowCurrent(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
}

void _Graphics::SetResizeCallback(GLFWwindow* window, void(*resize)(GLFWwindow*, int, int))
{
    glfwSetFramebufferSizeCallback(window, resize);
}

bool _Graphics::ShouldWindowClose(GLFWwindow* window)
{
    return glfwWindowShouldClose(window);
}

void _Graphics::SetWindowShouldClose(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, true);
}

void _Graphics::Clear(float r, float b, float g, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void _Graphics::SwapBuffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}

void _Graphics::PollForEvents()
{
    glfwPollEvents();
}

void _Graphics::Terminate()
{
    glfwTerminate();
}

void _Graphics::GenerateVertexArrays(unsigned int& ID, int n)
{
    glGenVertexArrays(n, &ID);
}

void _Graphics::GenerateBuffer(unsigned int& ID, int n)
{
    glGenBuffers(n, &ID);
}

void _Graphics::BindArray(unsigned int ID)
{
    glBindVertexArray(ID);
}

void _Graphics::BindBuffer(BufferType type, unsigned int ID, GLsizeiptr sizeptr, const void* data)
{
    glBindBuffer(Deserialise(type), ID);
    glBufferData(Deserialise(type), sizeptr, data, GL_STATIC_DRAW);
}

void _Graphics::VertexAttirbutePointer(int index, int size, GLsizei stride, const void* offset)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(index);
}

void _Graphics::UnbindBuffer(BufferType type)
{
    glBindBuffer(Deserialise(type), 0);
}

void _Graphics::UnbindArray()
{
    glBindVertexArray(0);
}

void _Graphics::DrawElements(Shape shapes, GLsizei count, DataType type, const void* indices)
{
    glDrawElements(Deserialise(shapes), count, Deserialise(type), indices);
}

void _Graphics::DrawArrays(Shape shapes, int first, GLsizei count)
{
    glDrawArrays(Deserialise(shapes), first, count);
}

void _Graphics::DeleteBuffers(unsigned int& ID, int n)
{
    glDeleteBuffers(n, &ID);
}

void _Graphics::DeleteArrays(unsigned int& ID, int n)
{
    glDeleteVertexArrays(n, &ID);
}

void _Graphics::DeleteProgram(unsigned int ID)
{
    glDeleteProgram(ID);
}




GLenum _Graphics::Deserialise(BufferType type)
{
    switch (type)
    {
    case BufferType::ARRAY:
        return GL_ARRAY_BUFFER;
    case BufferType::ELEMENT:
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}

GLenum _Graphics::Deserialise(Shape type)
{
    switch (type)
    {
    case Shape::TRIANGLES:
        return GL_TRIANGLES;
    }
}

GLenum _Graphics::Deserialise(DataType type)
{
    switch (type)
    {
    case DataType::FLOAT:
        return GL_FLOAT;
    case DataType::UNSIGNED_INT:
        return GL_UNSIGNED_INT;
    }
}

#include "Graphics.h"

double _Graphics::mScreenHeight = 0;
double _Graphics::mScreenWidth = 0;

void _Graphics::InitializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void _Graphics::InitializeGLAD()
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

    mScreenHeight = height;
    mScreenWidth = width;
    return window;
}

GLFWwindow* _Graphics::CreateWindow(std::string title)
{
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, title.c_str(), primary, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        std::cerr << "Failed to create a window" << std::endl;
        std::exit(0);
    }

    mScreenHeight = mode->height;
    mScreenWidth = mode->width;

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

void _Graphics::SetMouseButtonCallback(GLFWwindow* window, void(*mouseBtn)(GLFWwindow*, int, int, int))
{
    glfwSetMouseButtonCallback(window, mouseBtn);
}

void _Graphics::SetCursorCallback(GLFWwindow* window, void(*cursor)(GLFWwindow*, double, double))
{
    glfwSetCursorPosCallback(window, cursor);
}

void _Graphics::SetScrollCallback(GLFWwindow* window, void(*scroll)(GLFWwindow*, double, double))
{
    glfwSetScrollCallback(window, scroll);
}

void _Graphics::SetKeyboardCallback(GLFWwindow* window, void(*keys)(GLFWwindow*, int, int, int, int))
{
    glfwSetKeyCallback(window, keys);
}

void _Graphics::CaptureMouse(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void _Graphics::BindBuffer(BufferType type, unsigned int ID)
{
    glBindBuffer(Deserialise(type), ID);
}

void _Graphics::BindBufferAndData(BufferType type, unsigned int ID, GLsizeiptr sizeptr, const void* data)
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

void _Graphics::BindTextureOnUnit(Unit unit, unsigned int ID)
{
    glActiveTexture(Deserialise(unit));
    glBindTexture(GL_TEXTURE_2D, ID);
}

void _Graphics::SetWindowUserPointer(GLFWwindow* window, void* pointer)
{
    glfwSetWindowUserPointer(window, pointer);
}

void _Graphics::Enable(Capability cap)
{
    glEnable(Deserialise(cap));
}

void _Graphics::Disable(Capability cap)
{
    glDisable(Deserialise(cap));
}

float _Graphics::GetTime()
{
    return glfwGetTime();
}

double _Graphics::ScreenWidth()
{
    return mScreenWidth;
}

double _Graphics::ScreenHeight()
{
    return mScreenHeight;
}

float _Graphics::AspectRatio()
{
    return mScreenWidth / mScreenHeight;
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

GLenum _Graphics::Deserialise(Unit unit)
{
    switch (unit)
    {
    case Unit::ZERO:
        return GL_TEXTURE0;
    case Unit::ONE:
        return GL_TEXTURE1;
    case Unit::TWO:
        return GL_TEXTURE2;
    case Unit::THREE:
        return GL_TEXTURE3;
    case Unit::FOUR:
        return GL_TEXTURE4;
    case Unit::FIVE:
        return GL_TEXTURE5;
    case Unit::SIX:
        return GL_TEXTURE6;
    case Unit::SEVEN:
        return GL_TEXTURE7;
    case Unit::EIGHT:
        return GL_TEXTURE8;
    case Unit::NINE:
        return GL_TEXTURE9;
    }
}

GLenum _Graphics::Deserialise(Capability cap)
{
    switch (cap)
    {
    case Capability::DEPTH:
        return GL_DEPTH_TEST;
    }
}

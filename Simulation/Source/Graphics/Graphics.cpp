#include "Graphics/Graphics.h"

Graphics::Graphics(int width, int height, std::string title)
{
    InitializeGLFW();

    mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (mWindow == NULL)
    {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        std::exit(1);
    }

    mScreenHeight = height;
    mScreenWidth = width;
}

Graphics::~Graphics()
{
    Terminate();
}

GLFWwindow* Graphics::Window() const
{
    return mWindow;
}

void Graphics::InitializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Graphics::InitializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        std::exit(1);
    }
}

void Graphics::MakeWindowCurrent()
{
    glfwMakeContextCurrent(mWindow);
}

void Graphics::SetResizeCallback(void(*resize)(GLFWwindow*, int, int))
{
    glfwSetFramebufferSizeCallback(mWindow, resize);
}

void Graphics::SetMouseButtonCallback(void(*mouseBtn)(GLFWwindow*, int, int, int))
{
    glfwSetMouseButtonCallback(mWindow, mouseBtn);
}

void Graphics::SetCursorCallback(void(*cursor)(GLFWwindow*, double, double))
{
    glfwSetCursorPosCallback(mWindow, cursor);
}

void Graphics::SetScrollCallback(void(*scroll)(GLFWwindow*, double, double))
{
    glfwSetScrollCallback(mWindow, scroll);
}

void Graphics::SetKeyboardCallback(void(*keys)(GLFWwindow*, int, int, int, int))
{
    glfwSetKeyCallback(mWindow, keys);
}

void Graphics::CaptureMouse()
{
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Graphics::ShouldWindowClose()
{
    return glfwWindowShouldClose(mWindow);
}

void Graphics::SetWindowShouldClose()
{
    glfwSetWindowShouldClose(mWindow, true);
}

void Graphics::SetWindowShouldClose(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, true);
}

void Graphics::Clear(float r, float b, float g, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
}

void Graphics::PollForEvents()
{
    glfwPollEvents();
}

void Graphics::Terminate()
{
    glfwTerminate();
}

void Graphics::GenerateVertexArrays(unsigned int& ID, int n)
{
    glGenVertexArrays(n, &ID);
}

void Graphics::GenerateBuffer(unsigned int& ID, int n)
{
    glGenBuffers(n, &ID);
}

void Graphics::BindArray(unsigned int ID)
{
    glBindVertexArray(ID);
}

void Graphics::BindBuffer(BufferType type, unsigned int ID)
{
    glBindBuffer(Deserialise(type), ID);
}

void Graphics::BindBufferAndData(BufferType type, unsigned int ID, GLsizeiptr sizeptr, const void* data)
{
    glBindBuffer(Deserialise(type), ID);
    glBufferData(Deserialise(type), sizeptr, data, GL_STATIC_DRAW);
}

void Graphics::VertexAttirbutePointer(int index, int size, GLsizei stride, const void* offset)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(index);
}

void Graphics::UnbindBuffer(BufferType type)
{
    glBindBuffer(Deserialise(type), 0);
}

void Graphics::UnbindArray()
{
    glBindVertexArray(0);
}

void Graphics::DrawElements(Shape shapes, GLsizei count, DataType type, const void* indices)
{
    glDrawElements(Deserialise(shapes), count, Deserialise(type), indices);
}

void Graphics::DrawArrays(Shape shapes, int first, GLsizei count)
{
    glDrawArrays(Deserialise(shapes), first, count);
}

void Graphics::DeleteBuffers(unsigned int& ID, int n)
{
    glDeleteBuffers(n, &ID);
}

void Graphics::DeleteArrays(unsigned int& ID, int n)
{
    glDeleteVertexArrays(n, &ID);
}

void Graphics::DeleteProgram(unsigned int ID)
{
    glDeleteProgram(ID);
}

void Graphics::BindTextureOnUnit(Unit unit, unsigned int ID)
{
    glActiveTexture(Deserialise(unit));
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Graphics::SetWindowUserPointer(GLFWwindow* window, void* pointer)
{
    glfwSetWindowUserPointer(window, pointer);
}

void Graphics::Enable(Capability cap)
{
    glEnable(Deserialise(cap));
}

void Graphics::Disable(Capability cap)
{
    glDisable(Deserialise(cap));
}

float Graphics::GetTime()
{
    return glfwGetTime();
}

double Graphics::ScreenWidth() const
{
    return mScreenWidth;
}

double Graphics::ScreenHeight() const
{
    return mScreenHeight;
}

float Graphics::AspectRatio() const
{
    return mScreenWidth / mScreenHeight;
}

GLenum Graphics::Deserialise(BufferType type)
{
    switch (type)
    {
    case BufferType::ARRAY:
        return GL_ARRAY_BUFFER;
    case BufferType::ELEMENT:
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}

GLenum Graphics::Deserialise(Shape type)
{
    switch (type)
    {
    case Shape::TRIANGLES:
        return GL_TRIANGLES;
    }
}

GLenum Graphics::Deserialise(DataType type)
{
    switch (type)
    {
    case DataType::FLOAT:
        return GL_FLOAT;
    case DataType::UNSIGNED_INT:
        return GL_UNSIGNED_INT;
    }
}

GLenum Graphics::Deserialise(Unit unit)
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

GLenum Graphics::Deserialise(Capability cap)
{
    switch (cap)
    {
    case Capability::DEPTH:
        return GL_DEPTH_TEST;
    }
}

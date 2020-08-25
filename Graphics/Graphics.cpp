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

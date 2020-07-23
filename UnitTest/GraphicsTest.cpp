#include "GraphicsTest.h"

bool GraphicsTest::Test()
{
    bool allPassed;

    allPassed = DefaultWindowTest();

    return allPassed;
}

bool GraphicsTest::DefaultWindowTest()
{
    Graphics::InitializeGLFW();

    GLFWwindow* window = Graphics::CreateWindow(800, 500, "Default Window");

    Graphics::MakeContextCurrent(window);

    Graphics::AssignFrameBufferSizeCallback(window, [](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    Graphics::InitializeGlad();

    while (!Graphics::ShouldWindowClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            Graphics::SetWindowShouldClose(window);

        Graphics::Clear(1.0f, 0.5, 0.0f, 1.0f);

        Graphics::SwapBuffers(window);
        Graphics::PollForEvents();
    }

    Graphics::TerminateGLFW();

    return true;
}

#include "GraphicsTest.h"

#include <fstream>
#include <sstream>
#include <iostream>

bool GraphicsTest::Test()
{
    bool allPassed;

    allPassed = DefaultWindowTest();

	allPassed = Shaders();

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

bool GraphicsTest::Shaders()
{
    class ShaderObj
    {
    public:
        unsigned int ID;

        void New(const char* v, const char* f, const char* g)
        {
            ID = Shader::New(v, f, g);
        }
    };

    Graphics::InitializeGLFW();

    GLFWwindow* window = Graphics::CreateWindow(500, 800, "Shaders");
    Graphics::MakeContextCurrent(window);
    Graphics::AssignFrameBufferSizeCallback(window, [](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    Graphics::InitializeGlad();

    ShaderObj shader;
    shader.New("../Shaders/Vertex/3.3shader.vert", "../Shaders/Fragment/3.3shader.frag", nullptr);

    float vertices[] =
    {
         0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
        -0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
         0.0,  0.5, 0.0, 0.0, 0.0, 1.0
    };

    unsigned int VBO, VAO;
    Graphics::GenerateVertexArrays(&VAO);
    Graphics::GenerateBuffers(&VBO);

    Graphics::BindArray(VAO);

    Graphics::BindBuffer(VBO, sizeof(vertices), vertices);

    Graphics::VertexAttribPointer(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    Graphics::VertexAttribPointer(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    while (!Graphics::ShouldWindowClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            Graphics::SetWindowShouldClose(window);

        Graphics::Clear(0.2f, 0.3f, 0.3f, 1.0f);

        Shader::Use(shader.ID);

        Graphics::BindArray(VAO);
        Graphics::DrawArrays(GL_TRIANGLES, 0, 3);

        Graphics::SwapBuffers(window);
        Graphics::PollForEvents();
    }

    Graphics::DeleteArrays(&VAO, 1);
    Graphics::DeleteBuffers(&VBO, 1);

    Graphics::TerminateGLFW();

    return true;
}

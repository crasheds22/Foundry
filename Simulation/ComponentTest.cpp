#include "ComponentTest.h"

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        _Graphics::SetWindowShouldClose(window);
}

bool ComponentTest::Test()
{
    bool allPassed = false;

    allPassed = ShaderComponent();
    allPassed = TextureComponent();
    allPassed = ModelComponent();
    allPassed = CameraComponent();

    return allPassed;
}

bool ComponentTest::ShaderComponent()
{
    _Graphics::InitializeGLFW();

    // glfw window creation
    // --------------------
    GLFWwindow* window = _Graphics::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "Using shaders");
    _Graphics::MakeWindowCurrent(window);
    _Graphics::SetResizeCallback(window, [](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    _Graphics::InitializeGLAD();

    // build and compile our shader program
    // ------------------------------------
    Component::com_Shader ourShader("../Data/Shaders/3.3.shader.vs", "../Data/Shaders/3.3.shader.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    unsigned int VBO, VAO;
    _Graphics::GenerateVertexArrays(VAO);
    _Graphics::GenerateBuffer(VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    _Graphics::BindArray(VAO);

    _Graphics::BindBufferAndData(_Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    // position attribute
    _Graphics::VertexAttirbutePointer(0, 3, 6 * sizeof(float), (void*)0);
    // color attribute
    _Graphics::VertexAttirbutePointer(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------
    while (!_Graphics::ShouldWindowClose(window))
    {
        // input
        // -----
        ProcessInput(window);

        // render
        // ------
        _Graphics::Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // render the triangle
        ourShader.Use();
        _Graphics::BindArray(VAO);
        _Graphics::DrawArrays(_Graphics::Shape::TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        _Graphics::SwapBuffers(window);
        _Graphics::PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    _Graphics::DeleteArrays(VAO, 1);
    _Graphics::DeleteBuffers(VBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    _Graphics::Terminate();

    return true;
}

bool ComponentTest::TextureComponent()
{
    return false;
}

bool ComponentTest::ModelComponent()
{
    return false;
}

bool ComponentTest::CameraComponent()
{
    return false;
}

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
    // glfw: initialize and configure
    // ------------------------------
    _Graphics::InitializeGLFW();

    // glfw window creation
    // --------------------
    GLFWwindow* window = _Graphics::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "Textures");
    _Graphics::MakeWindowCurrent(window);
    _Graphics::SetResizeCallback(window, [](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    _Graphics::InitializeGLAD();

    // build and compile our shader zprogram
    // ------------------------------------
    Component::com_Shader ourShader("../Data/Shaders/4.2.texture.vs", "../Data/Shaders/4.2.texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    _Graphics::GenerateVertexArrays(VAO);
    _Graphics::GenerateBuffer(VBO);
    _Graphics::GenerateBuffer(EBO);

    _Graphics::BindArray(VAO);

    _Graphics::BindBufferAndData(_Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    _Graphics::BindBufferAndData(_Graphics::BufferType::ELEMENT, EBO, sizeof(indices), indices);

    // position attribute
    _Graphics::VertexAttirbutePointer(0, 3, 8 * sizeof(float), (void*)0);
    // color attribute
    _Graphics::VertexAttirbutePointer(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // texture coord attribute
    _Graphics::VertexAttirbutePointer(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    Texture::FlipVertically();
    Component::com_Texture texture1("../Data/Textures/container.jpg");
    Component::com_Texture texture2("../Data/Textures/awesomeface.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.Use(); // don't forget to activate/use the shader before setting uniforms!
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

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

        // bind textures on corresponding texture units
        _Graphics::BindTextureOnUnit(_Graphics::Unit::ZERO, texture1.ID());
        _Graphics::BindTextureOnUnit(_Graphics::Unit::ONE, texture2.ID());

        // render container
        ourShader.Use();
        _Graphics::BindArray(VAO);
        _Graphics::DrawElements(_Graphics::Shape::TRIANGLES, 6, _Graphics::DataType::UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        _Graphics::SwapBuffers(window);
        _Graphics::PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    _Graphics::DeleteArrays(VAO, 1);
    _Graphics::DeleteBuffers(VBO, 1);
    _Graphics::DeleteBuffers(EBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    _Graphics::Terminate();

    return true;
}

bool ComponentTest::ModelComponent()
{
    return false;
}

bool ComponentTest::CameraComponent()
{
    return false;
}

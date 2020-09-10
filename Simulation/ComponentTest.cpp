#include "ComponentTest.h"

void ProcessInput(GLFWwindow* window, Component::com_Camera* camera = nullptr, float dt = 0.0f)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        _Graphics::SetWindowShouldClose(window);

    if (camera)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::FORWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::LEFT, dt);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::BACKWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::RIGHT, dt);
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    ComponentTest* This = (ComponentTest*)glfwGetWindowUserPointer(window);

    if (This->FirstMouse)
    {
        This->lastX = xPos;
        This->lastY = yPos;
        This->FirstMouse = false;
    }

    float xOff = xPos - This->lastX;
    float yOff = This->lastY - yPos;

    This->lastX = xPos;
    This->lastY = yPos;

    This->camera.RotateCamera(xOff, yOff);
}

void ScrollCallback(GLFWwindow* window, double xOff, double yOff)
{
    ComponentTest* This = (ComponentTest*)glfwGetWindowUserPointer(window);

    This->camera.Zoom(yOff);
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
    camera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    // glfw: initialize and configure
    // ------------------------------
    _Graphics::InitializeGLFW();

    // glfw window creation
    // --------------------
    GLFWwindow* window = _Graphics::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "Camera and Cubes");
    _Graphics::MakeWindowCurrent(window);
    _Graphics::SetWindowUserPointer(window, this);
    _Graphics::SetResizeCallback(window, [](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    _Graphics::SetCursorCallback(window, MouseCallback);
    _Graphics::SetScrollCallback(window, ScrollCallback);

    // tell GLFW to capture our mouse
    _Graphics::CaptureMouse(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    _Graphics::InitializeGLAD();

    // configure global opengl state
    // -----------------------------
    _Graphics::Enable(_Graphics::Capability::DEPTH);

    // build and compile our shader zprogram
    // ------------------------------------
    Component::com_Shader ourShader("../Data/Shaders/7.4.camera.vs", "../Data/Shaders/7.4.camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int VBO, VAO;
    _Graphics::GenerateVertexArrays(VAO);
    _Graphics::GenerateBuffer(VBO);

    _Graphics::BindArray(VAO);

    _Graphics::BindBufferAndData(_Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    // position attribute
    _Graphics::VertexAttirbutePointer(0, 3, 5 * sizeof(float), (void*)0);
    // texture coord attribute
    _Graphics::VertexAttirbutePointer(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));


    // load and create a texture 
    // -------------------------
    Texture::FlipVertically();
    Component::com_Texture texture1("../Data/Textures/container.jpg");
    Component::com_Texture texture2("../Data/Textures/awesomeface.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.Use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    // render loop
    // -----------
    while (!_Graphics::ShouldWindowClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = _Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(window, &camera, deltaTime);

        // render
        // ------
        _Graphics::Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // bind textures on corresponding texture units
        _Graphics::BindTextureOnUnit(_Graphics::Unit::ZERO, texture1.ID());
        _Graphics::BindTextureOnUnit(_Graphics::Unit::ONE, texture2.ID());

        // activate shader
        ourShader.Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)800 / (float)500, 0.1f, 100.0f);
       ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.ViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        _Graphics::BindArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            _Graphics::DrawArrays(_Graphics::Shape::TRIANGLES, 0, 36);
        }

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

    return false;
}

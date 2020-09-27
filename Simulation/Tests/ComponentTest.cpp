#include "ComponentTest.h"

void ProcessInput(GLFWwindow* window, Component::com_Camera* camera = nullptr, float dt = 0.0f)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Graphics::SetWindowShouldClose(window);

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

    allPassed = TextureComponent();
    allPassed = RenderComponent();
    allPassed = CameraComponent();

    return allPassed;
}

bool ComponentTest::TextureComponent()
{
    Graphics graphics = Graphics(SCR_WIDTH, SCR_HEIGHT, "Textures");
    graphics.MakeWindowCurrent();
    graphics.SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

    graphics.InitializeGLAD();

    // build and compile our shader zprogram
    // ------------------------------------
    ResMgr->CreateShader("4.2.texture", "../Data/Shaders/4.2.texture.vs", "../Data/Shaders/4.2.texture.fs");

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
    Graphics::GenerateVertexArrays(VAO);
    Graphics::GenerateBuffer(VBO);
    Graphics::GenerateBuffer(EBO);

    Graphics::BindArray(VAO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    Graphics::BindBufferAndData(Graphics::BufferType::ELEMENT, EBO, sizeof(indices), indices);

    // position attribute
    Graphics::VertexAttirbutePointer(0, 3, 8 * sizeof(float), (void*)0);
    // color attribute
    Graphics::VertexAttirbutePointer(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // texture coord attribute
    Graphics::VertexAttirbutePointer(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    TextureLoader::FlipVertically();
    ResMgr->CreateTexture("container", "../Data/Textures/container.jpg");
    ResMgr->CreateTexture("awesomeface", "../Data/Textures/awesomeface.png");

    Component::com_Texture texture1("container");
    Component::com_Texture texture2("awesomeface");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    Shader* ourShader = ResMgr->RetrieveShader("4.2.texture");
    ourShader->Use(); // don't forget to activate/use the shader before setting uniforms!
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);

    // render loop
    // -----------
    while (!graphics.ShouldWindowClose())
    {
        // input
        // -----
        ProcessInput(graphics.Window());

        // render
        // ------
        graphics.Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // bind textures on corresponding texture units
        Graphics::BindTextureOnUnit(Graphics::Unit::ZERO, texture1.TextureID());
        Graphics::BindTextureOnUnit(Graphics::Unit::ONE, texture2.TextureID());

        // render container
        ourShader->Use();
        Graphics::BindArray(VAO);
        Graphics::DrawElements(Graphics::Shape::TRIANGLES, 6, Graphics::DataType::UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics.SwapBuffers();
        graphics.PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(VAO, 1);
    Graphics::DeleteBuffers(VBO, 1);
    Graphics::DeleteBuffers(EBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics.Terminate();

    return true;
}

bool ComponentTest::RenderComponent()
{
    camera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;
    
    Graphics graphics = Graphics(SCR_WIDTH, SCR_HEIGHT, "Model One");
    graphics.MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics.Window(), this);
    graphics.SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics.SetCursorCallback(MouseCallback);
    graphics.SetScrollCallback(ScrollCallback);

    // tell GLFW to capture our mouse
    graphics.CaptureMouse();

    graphics.InitializeGLAD();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    TextureLoader::FlipVertically();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile shaders
    // -------------------------
    ResMgr->CreateShader("1.model", "../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");

    // load models
    // -----------
    ResMgr->CreateModel("../Data/Models/Backpack/backpack.obj");

    Component::com_Render ourRender("backpack", "1.model");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!graphics.ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics.Window(), &camera, deltaTime);

        // render
        // ------
        graphics.Clear(0.05f, 0.05f, 0.05f, 1.0f);

        // don't forget to enable shader before setting uniforms
        ourRender._Shader()->Use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.ViewMatrix();
        ourRender._Shader()->setMat4("projection", projection);
        ourRender._Shader()->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourRender._Shader()->setMat4("model", model);

        ourRender._Model()->Draw(ourRender._Shader()->ID());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics.SwapBuffers();
        graphics.PollForEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics.Terminate();

    return true;
}

bool ComponentTest::CameraComponent()
{
    camera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    Graphics graphics = Graphics(SCR_WIDTH, SCR_HEIGHT, "Camera and Cubes");
    graphics.MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics.Window(), this);
    graphics.SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics.SetCursorCallback(MouseCallback);
    graphics.SetScrollCallback(ScrollCallback);

    // tell GLFW to capture our mouse
    graphics.CaptureMouse();

    graphics.InitializeGLAD();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile our shader zprogram
    // ------------------------------------
    ResMgr->CreateShader("7.4.camera", "../Data/Shaders/7.4.camera.vs", "../Data/Shaders/7.4.camera.fs");
    Shader* ourShader = ResMgr->RetrieveShader("7.4.camera");

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
    Graphics::GenerateVertexArrays(VAO);
    Graphics::GenerateBuffer(VBO);

    Graphics::BindArray(VAO);

    Graphics::BindBufferAndData(Graphics::BufferType::ARRAY, VBO, sizeof(vertices), vertices);

    // position attribute
    Graphics::VertexAttirbutePointer(0, 3, 5 * sizeof(float), (void*)0);
    // texture coord attribute
    Graphics::VertexAttirbutePointer(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));


    // load and create a texture 
    // -------------------------
    TextureLoader::FlipVertically();
    ResMgr->CreateTexture("container", "../Data/Textures/container.jpg");
    ResMgr->CreateTexture("awesomeface", "../Data/Textures/awesomeface.png");

    Component::com_Texture texture1("container");
    Component::com_Texture texture2("awesomeface");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->Use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);


    // render loop
    // -----------
    while (!graphics.ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics.Window(), &camera, deltaTime);

        // render
        // ------
        graphics.Clear(0.2f, 0.3f, 0.3f, 1.0f);

        // bind textures on corresponding texture units
        Graphics::BindTextureOnUnit(Graphics::Unit::ZERO, texture1.TextureID());
        Graphics::BindTextureOnUnit(Graphics::Unit::ONE, texture2.TextureID());

        // activate shader
        ourShader->Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)800 / (float)500, 0.1f, 100.0f);
       ourShader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.ViewMatrix();
        ourShader->setMat4("view", view);

        // render boxes
        Graphics::BindArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader->setMat4("model", model);

            Graphics::DrawArrays(Graphics::Shape::TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics.SwapBuffers();
        graphics.PollForEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Graphics::DeleteArrays(VAO, 1);
    Graphics::DeleteBuffers(VBO, 1);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics.Terminate();

    return true;
}

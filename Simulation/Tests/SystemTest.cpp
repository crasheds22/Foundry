#include "SystemTest.h"

#include "ECS/Coordinator.h"
ECS::Coordinator gCoordinator;

void SystemTest::ProcessInput(GLFWwindow* window, Component::com_Camera* camera = nullptr, float dt = 0.0f)
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

void SystemTest::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    SystemTest* This = (SystemTest*)glfwGetWindowUserPointer(window);

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

void SystemTest::ScrollCallback(GLFWwindow* window, double xOff, double yOff)
{
    SystemTest* This = (SystemTest*)glfwGetWindowUserPointer(window);

    This->camera.Zoom(yOff);
}

SystemTest::SystemTest() : UnitTest("Systems test")
{
    
}

bool SystemTest::Test()
{
    bool allPassed = false;

    //allPassed = RenderSystem();

    allPassed = ControlSystem();

    return allPassed;
}

bool SystemTest::RenderSystem()
{
    camera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    Graphics graphics = Graphics(800, 500, "Model One");
    graphics.MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics.Window(), this);
    graphics.SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics.SetCursorCallback(MouseCallback);
    graphics.SetScrollCallback(ScrollCallback);

    // tell GLFW to capture our mouse
    graphics.CaptureMouse();

    graphics.InitializeGLAD();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    Texture::FlipVertically();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile shaders
    // -------------------------
    Component::com_Shader ourShader("../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");

    // load models
    // -----------
    Component::com_Model ourModel("../Data/Models/Backpack/backpack.obj");

    Component::com_Transform ourTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));

    gCoordinator.Init();

    gCoordinator.RegisterComponent<Component::com_Camera>();
    gCoordinator.RegisterComponent<Component::com_Model>();
    gCoordinator.RegisterComponent<Component::com_Shader>();
    gCoordinator.RegisterComponent<Component::com_Transform>();

    auto RenderSystem = gCoordinator.RegisterSystem<System::sys_Render>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Model>());
        sig.set(gCoordinator.GetComponentType<Component::com_Shader>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_Render>(sig);
    }

    auto backpack = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Model>(backpack, ourModel);
    gCoordinator.AddComponent<Component::com_Shader>(backpack, ourShader);
    gCoordinator.AddComponent<Component::com_Transform>(backpack, ourTransform);

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

        graphics.Clear(0.2f, 0.3f, 0.3f, 1.0f);

        RenderSystem->Update(&camera, &graphics);

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

bool SystemTest::ControlSystem()
{
    camera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    Graphics graphics = Graphics(800, 500, "Model One");
    graphics.MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics.Window(), this);
    graphics.SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics.SetCursorCallback(MouseCallback);
    graphics.SetScrollCallback(ScrollCallback);

    // tell GLFW to capture our mouse
    graphics.CaptureMouse();

    graphics.InitializeGLAD();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    Texture::FlipVertically();

    // configure global opengl state
    // -----------------------------
    Graphics::Enable(Graphics::Capability::DEPTH);

    // build and compile shaders
    // -------------------------
    Component::com_Shader ourShader("../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");

    // load models
    // -----------
    Component::com_Model ourModel("../Data/Models/Backpack/backpack.obj");

    Component::com_Transform ourTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));

    gCoordinator.Init();

    gCoordinator.RegisterComponent<Component::com_Camera>();
    gCoordinator.RegisterComponent<Component::com_Model>();
    gCoordinator.RegisterComponent<Component::com_Shader>();
    gCoordinator.RegisterComponent<Component::com_Transform>();

    auto RenderSystem = gCoordinator.RegisterSystem<System::sys_Render>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Model>());
        sig.set(gCoordinator.GetComponentType<Component::com_Shader>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_Render>(sig);
    }

    auto backpack = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Model>(backpack, ourModel);
    gCoordinator.AddComponent<Component::com_Shader>(backpack, ourShader);
    gCoordinator.AddComponent<Component::com_Transform>(backpack, ourTransform);

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

        graphics.Clear(0.2f, 0.3f, 0.3f, 1.0f);

        RenderSystem->Update(&camera, &graphics);

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

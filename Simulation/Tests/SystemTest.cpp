#include "SystemTest.h"

#include "ECS/Coordinator.h"
extern     ECS::Coordinator gCoordinator;

float SPEED = 2.5f;
float SENSITIVITY = 0.1f;

void SystemTest::ProcessInput(GLFWwindow* window, Component::com_Camera* camera = nullptr, float dt = 0.0f)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Graphics::SetWindowShouldClose(window);

    if (camera)
    {
        float v = dt * SPEED;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::FORWARD, v);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::LEFT, v);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::BACKWARD, v);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->MoveCamera(Component::Direction::RIGHT, v);
    }
}

void SystemTest::ProcessMouse()
{
    double xOff = ref->MouseOffset().first;
    double yOff = ref->MouseOffset().second;

    camera.RotateCamera(xOff * SENSITIVITY, yOff * SENSITIVITY);
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

    This->camera.RotateCamera(xOff * SENSITIVITY, yOff * SENSITIVITY);
}

void SystemTest::ProcessInput(Graphics* context)
{
    if (ref)
    {
        if (ref->Pressed(Actions::Global::QUIT))
            context->SetWindowShouldClose();

        float v = ref->DeltaTime() * SPEED;

        if (ref->Pressed(Actions::Move::FORWARD))
            camera.MoveCamera(Component::Direction::FORWARD, v);
        if (ref->Pressed(Actions::Move::BACKWARD))
            camera.MoveCamera(Component::Direction::BACKWARD, v);
        if (ref->Pressed(Actions::Move::LEFT))
            camera.MoveCamera(Component::Direction::LEFT, v);
        if (ref->Pressed(Actions::Move::RIGHT))
            camera.MoveCamera(Component::Direction::RIGHT, v);
    }
}

void SystemTest::ScrollCallback(GLFWwindow* window, double xOff, double yOff)
{
    SystemTest* This = (SystemTest*)glfwGetWindowUserPointer(window);

    This->camera.Zoom(yOff);
}

SystemTest::SystemTest() : UnitTest("Systems test")
{
    ResMgr->Init();
}

bool SystemTest::Test()
{
    bool allPassed = false;

    //allPassed = RenderSystem();

    //allPassed = ControlSystem();

    allPassed = PhysicsSystem();

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

    Graphics* graphics = &Graphics::Instance();
    graphics->Init(800, 500, "Model One");
    graphics->MakeWindowCurrent();
    Graphics::SetWindowUserPointer(graphics->Window(), this);
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    graphics->SetCursorCallback(MouseCallback);
    graphics->SetScrollCallback(ScrollCallback);

    // tell GLFW to capture our mouse
    graphics->CaptureMouse();

    graphics->InitializeGLAD();

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

    Component::com_Render ourRender("backpack.obj", "1.model");
    Component::com_Transform ourTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));

    gCoordinator.Init();

    gCoordinator.RegisterComponent<Component::com_Camera>();
    gCoordinator.RegisterComponent<Component::com_Render>();
    gCoordinator.RegisterComponent<Component::com_Transform>();

    auto RenderSystem = gCoordinator.RegisterSystem<System::sys_Render>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Render>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_Render>(sig);
    }

    auto backpack = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Render>(backpack, ourRender);
    gCoordinator.AddComponent<Component::com_Transform>(backpack, ourTransform);

    // render loop
    // -----------
    while (!graphics->ShouldWindowClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(graphics->Window(), &camera, deltaTime);

        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        RenderSystem->Update(&camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    graphics->Terminate();

    return true;
}

bool SystemTest::ControlSystem()
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    Graphics* graphics = &Graphics::Instance();
    graphics->Init(800, 500, "Model One");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });

    graphics->CaptureMouse();
    graphics->StickyKeys();

    graphics->InitializeGLAD();

    TextureLoader::FlipVertically();

    Graphics::Enable(Graphics::Capability::DEPTH);

    ref = &Props::Instance();

    ResMgr->CreateShader("1.model", "../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");
    ResMgr->CreateModel("../Data/Models/Backpack/backpack.obj");

    Component::com_Transform camTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));
    Component::com_Render ourRender("backpack.obj", "1.model");

    Component::com_Camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));
    Component::com_Player ourPlayer(2.5f, 0.1f);
    Component::com_Transform plaTransform(ourCamera.Position(), glm::vec3(0), glm::vec3(1));

    gCoordinator.Init();

    gCoordinator.RegisterComponent<Component::com_Camera>();
    gCoordinator.RegisterComponent<Component::com_Render>();
    gCoordinator.RegisterComponent<Component::com_Transform>();
    gCoordinator.RegisterComponent<Component::com_Player>();

    auto RenderSystem = gCoordinator.RegisterSystem<System::sys_Render>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Render>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_Render>(sig);
    }
    RenderSystem->Init();

    auto PlayerControlSystem = gCoordinator.RegisterSystem<System::sys_PlayerControl>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Player>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_PlayerControl>(sig);
    }
    PlayerControlSystem->Init();

    auto backpack = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Render>(backpack, ourRender);
    gCoordinator.AddComponent<Component::com_Transform>(backpack, camTransform);

    auto player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Player>(player, ourPlayer);
    gCoordinator.AddComponent<Component::com_Transform>(player, plaTransform);

    while (!graphics->ShouldWindowClose())
    {
        ref->UpdateDT();

        ref->UpdateKeys();
        ref->UpdateMouse();

        if (ref->Pressed(Actions::Global::QUIT))
            graphics->SetWindowShouldClose();

        PlayerControlSystem->Update(&ourCamera);

        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        RenderSystem->Update(&ourCamera);

        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    graphics->Terminate();

    return true;
}

bool SystemTest::PhysicsSystem()
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 500.0f / 2.0f;
    FirstMouse = true;

    Graphics* graphics = &Graphics::Instance();
    graphics->Init(800, 500, "Model One");
    graphics->MakeWindowCurrent();
    graphics->SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });

    graphics->CaptureMouse();
    graphics->StickyKeys();

    graphics->InitializeGLAD();

    TextureLoader::FlipVertically();

    Graphics::Enable(Graphics::Capability::DEPTH);

    ref = &Props::Instance();

    //Create resources: models, shaders, textures
    ResMgr->CreateShader("1.model", "../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs");
    ResMgr->CreateModel("../Data/Models/Backpack/backpack.obj");

    //Create components
    Component::com_Transform camTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));
    Component::com_Render ourRender("backpack.obj", "1.model");

    Component::com_Camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));
    Component::com_Player ourPlayer(2.5f, 0.1f);
    Component::com_Transform plaTransform(ourCamera.Position(), glm::vec3(0), glm::vec3(1));

    //Initialise ECS
    gCoordinator.Init();

    //Register components
    gCoordinator.RegisterComponent<Component::com_Camera>();
    gCoordinator.RegisterComponent<Component::com_Render>();
    gCoordinator.RegisterComponent<Component::com_Transform>();
    gCoordinator.RegisterComponent<Component::com_Player>();
    gCoordinator.RegisterComponent<Component::com_Physics>();

    //Create and register Systems
    auto RenderSystem = gCoordinator.RegisterSystem<System::sys_Render>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Render>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_Render>(sig);
    }
    RenderSystem->Init();

    auto PlayerControlSystem = gCoordinator.RegisterSystem<System::sys_PlayerControl>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Player>());
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        gCoordinator.SetSystemSignature<System::sys_PlayerControl>(sig);
    }
    PlayerControlSystem->Init();

    auto PhysicsSystem = gCoordinator.RegisterSystem<System::sys_Physics>();
    {
        ECS::Signature sig;
        sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
        sig.set(gCoordinator.GetComponentType<Component::com_Physics>());
        gCoordinator.SetSystemSignature<System::sys_Physics>(sig);
    }
    PhysicsSystem->Init();

    //Create entities here
    auto backpack = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Render>(backpack, ourRender);
    gCoordinator.AddComponent<Component::com_Transform>(backpack, camTransform);

    auto player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<Component::com_Player>(player, ourPlayer);
    gCoordinator.AddComponent<Component::com_Transform>(player, plaTransform);

    //loop
    while (!graphics->ShouldWindowClose())
    {
        ref->UpdateDT();

        ref->UpdateKeys();
        ref->UpdateMouse();

        if (ref->Pressed(Actions::Global::QUIT))
            graphics->SetWindowShouldClose();

        PlayerControlSystem->Update(&ourCamera);

        graphics->Clear(0.2f, 0.3f, 0.3f, 1.0f);

        PhysicsSystem->Update();

        RenderSystem->Update(&ourCamera);

        graphics->SwapBuffers();
        graphics->PollForEvents();
    }

    graphics->Terminate();

    return true;
}

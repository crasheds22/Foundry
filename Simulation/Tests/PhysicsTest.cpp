#include "PhysicsTest.h"

#include "ECS/Coordinator.h"
extern     ECS::Coordinator gCoordinator;

bool PhysicsTest::ControlSystem()
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
#include "SystemTest.h"

#include "Coordinator.h"
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

    allPassed = RenderSystem();

    return allPassed;
}

bool SystemTest::RenderSystem()
{
    camera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    Graphics gGraphics = Graphics(800.0f, 500.0f, "Model System");
    gGraphics.MakeWindowCurrent();
    Graphics::SetWindowUserPointer(gGraphics.Window(), this);
    gGraphics.SetResizeCallback([](GLFWwindow* win, int w, int h) {glViewport(0, 0, w, h); });
    gGraphics.SetCursorCallback(SystemTest::MouseCallback);
    gGraphics.SetScrollCallback(SystemTest::ScrollCallback);

    gGraphics.CaptureMouse();

    gGraphics.InitializeGLAD();

    Texture::FlipVertically();

    Graphics::Enable(Graphics::Capability::DEPTH);

    gCoordinator.Init();

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
    gCoordinator.AddComponent(backpack, Component::com_Model("../Data/Models/Backpack/backpack.obj"));
    gCoordinator.AddComponent(backpack, Component::com_Shader("../Data/Shaders/1.model_loading.vs", "../Data/Shaders/1.model_loading.fs"));
    gCoordinator.AddComponent(backpack, Component::com_Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1)));

    while (!gGraphics.ShouldWindowClose())
    {
        float currentFrame = Graphics::GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(gGraphics.Window(), &camera, deltaTime);

        gGraphics.Clear(0.05f, 0.05f, 0.05f, 1.0f);

        RenderSystem->Update(&camera, gGraphics);

        gGraphics.SwapBuffers();
        gGraphics.PollForEvents();
    }

    gGraphics.Terminate();

    return true;
}

#include "Theatre.h"

Theatre::Theatre()
{
	mGraphics = &Graphics::Instance();

	mResourceManager = &Resource::ResourceManager::Instance();

	mActiveSystems = &SystemsManager::Instance();

	mProps = &Props::Instance();
}

Theatre::~Theatre()
{
	mGraphics = nullptr;

	mResourceManager = nullptr;

	mActiveSystems = nullptr;

	mProps = nullptr;
}

void Theatre::PreShow()
{
	//Graphics
	mGraphics->Init(800, 500, "Simulation");
	mGraphics->MakeWindowCurrent();
	mGraphics->SetResizeCallback([](GLFWwindow* win, int w, int h) { glViewport(0, 0, w, h); });

	mGraphics->CaptureMouse();
	mGraphics->StickyKeys();

	mGraphics->InitializeGLAD();

	TextureLoader::FlipVertically();

	mGraphics->Enable(Graphics::Capability::DEPTH);

	//Resources
	mResourceManager->CreateModel("Data/Models/Backpack/backpack.obj");

	mResourceManager->CreateShader("backpack", "Data/Shaders/1.model_loading.vs", "Data/Shaders/1.model_loading.fs");


	//ECS
	gCoordinator.Init();
	//	Components
	gCoordinator.RegisterComponent<Component::com_Camera>();
	gCoordinator.RegisterComponent<Component::com_Physics>();
	gCoordinator.RegisterComponent<Component::com_Player>();
	gCoordinator.RegisterComponent<Component::com_Render>();
	gCoordinator.RegisterComponent<Component::com_Texture>();
	gCoordinator.RegisterComponent<Component::com_Transform>();

	//	Systems
	auto RenderSys = gCoordinator.RegisterSystem<System::sys_Render>();
	{
		ECS::Signature sig;
		sig.set(gCoordinator.GetComponentType<Component::com_Render>());
		sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
		gCoordinator.SetSystemSignature<System::sys_Render>(sig);
	}

	mActiveSystems->Create("RenderSystem", RenderSys);

	auto PlayerSys = gCoordinator.RegisterSystem<System::sys_PlayerControl>();
	{
		ECS::Signature sig;
		sig.set(gCoordinator.GetComponentType<Component::com_Player>());
		sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
		gCoordinator.SetSystemSignature<System::sys_PlayerControl>(sig);
	}

	mActiveSystems->Create("PlayerSystem", PlayerSys);

	PlayShow();
}

void Theatre::PlayShow()
{
	while (!mGraphics->ShouldWindowClose())
	{
		mProps->UpdateDT();

		mProps->UpdateKeys();
		mProps->UpdateMouse();

		if (mProps->Pressed(Actions::Global::QUIT))
			mGraphics->SetWindowShouldClose();

		mGraphics->Clear(135 / 256, 206 / 256, 235 / 256, 1.0f);

		mActiveStage.Update();

		mGraphics->SwapBuffers();
		mGraphics->PollForEvents();
	}

	EndShow();
}

void Theatre::EndShow()
{
	mGraphics->Terminate();
}

#include "Stage.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

Stage::Stage()
{
	mResources = &Resource::ResourceManager::Instance();
}

Stage::~Stage()
{
	mResources = nullptr;
}

void Stage::Init()
{
	//	Systems
	RenderSys = gCoordinator.RegisterSystem<System::sys_Render>();
	{
		ECS::Signature sig;
		sig.set(gCoordinator.GetComponentType<Component::com_Render>());
		sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
		gCoordinator.SetSystemSignature<System::sys_Render>(sig);
	}

	RenderSys->Init();

	PlayerSys = gCoordinator.RegisterSystem<System::sys_PlayerControl>();
	{
		ECS::Signature sig;
		sig.set(gCoordinator.GetComponentType<Component::com_Player>());
		sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
		gCoordinator.SetSystemSignature<System::sys_PlayerControl>(sig);
	}

	PlayerSys->Init();

	mCamera = Component::com_Camera(glm::vec3(0.0f, 4.0f, 3.0f));

	//Create entities here
	auto maars = gCoordinator.CreateEntity();
	{
		gCoordinator.AddComponent<Component::com_Render>(maars, Component::com_Render("MaARS", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(maars, Component::com_Transform(glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(1)));
	}

	for (auto pair : mResources->RetrieveWorld("MaARS")->SpawnPoints())
	{
		for (int i = 0; i < pair.second.size(); i++)
		{
			Create(pair.first + std::to_string(i), Prototype::Factory::Make(pair.first, Component::com_Transform(pair.second[i], glm::vec3(0), glm::vec3(1))));
		}
	}

	auto backpack = gCoordinator.CreateEntity();
	{
		gCoordinator.AddComponent<Component::com_Render>(backpack, Component::com_Render("backpack", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(backpack, Component::com_Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1)));
	}
	
	auto player = gCoordinator.CreateEntity();
	{
		gCoordinator.AddComponent<Component::com_Player>(player, Component::com_Player(2.5f, 0.1f));
		gCoordinator.AddComponent<Component::com_Transform>(player, Component::com_Transform(mCamera.Position(), glm::vec3(0), glm::vec3(1)));
	}
}

void Stage::Update()
{
	PlayerSys->Update(&mCamera);

	RenderSys->Update(&mCamera);
}

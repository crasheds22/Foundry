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
	Create("MaARS", new Prototype::World("MaARS"));
	for (auto pair : mResources->RetrieveWorld("MaARS")->SpawnPoints())
	{
		for (int i = 0; i < pair.second.size(); i++)
			Create(pair.first + "_" + std::to_string(i), Prototype::Factory::Make(pair.first, Component::com_Transform(pair.second[i], glm::vec3(0), glm::vec3(1))));
	}

	Create("Backpack", Prototype::Factory::Make("backpack", Component::com_Transform(glm::vec3(0, 1, 0), glm::vec3(0), glm::vec3(1))));
	Create("Player", Prototype::Factory::Make("player", Component::com_Transform(glm::vec3(mCamera.Position()), glm::vec3(0), glm::vec3(0))));
}

void Stage::Update()
{
	PlayerSys->Update(&mCamera);

	RenderSys->Update(&mCamera);
}

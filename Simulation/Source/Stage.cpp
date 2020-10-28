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

	PhysicsSys = gCoordinator.RegisterSystem<System::sys_Physics>();
	{
		ECS::Signature sig;
		sig.set(gCoordinator.GetComponentType<Component::com_Physics>());
		sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
		gCoordinator.SetSystemSignature<System::sys_Physics>(sig);
	}

	PhysicsSys->Init();

	mCamera = Component::com_Camera(glm::vec3(0.0f, 4.0f, 3.0f));

	//Create entities here
	Create("MaARS", new Prototype::World("MaARS"));
	for (auto pair : mResources->RetrieveWorld("MaARS")->SpawnPoints())
	{
		for (int i = 0; i < pair.second.size(); i++)
			Create(pair.first + "_" + std::to_string(i), Prototype::Factory::Make(pair.first
																				, Component::com_Transform(pair.second[i].first, glm::vec3(0), glm::vec3(1))
																				, pair.second[i].second));
	}

	Create("Player", Prototype::Factory::Make("player"
											, Component::com_Transform(glm::vec3(mCamera.Position()), glm::vec3(0), glm::vec3(0))
											, std::pair<glm::vec3, glm::vec3>(glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(-1.0f, -2.0f, -1.0f))));
}

void Stage::Update()
{
	PlayerSys->Update(&mCamera);

	RenderSys->Update(&mCamera);

	PhysicsSys->Update();
}

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

	mCamera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//Create entities here
	auto backpack = gCoordinator.CreateEntity();
		Component::com_Render	 backpackRender("backpack.obj", "backpack");
		Component::com_Transform backpackTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));

	gCoordinator.AddComponent<Component::com_Render>   (backpack, backpackRender);
	gCoordinator.AddComponent<Component::com_Transform>(backpack, backpackTransform);

	Create("Backpack_01", backpack);

	auto player = gCoordinator.CreateEntity();
		Component::com_Player playerPlayer(2.5f, 0.1f);
		Component::com_Transform playerTransform(mCamera.Position(), glm::vec3(0), glm::vec3(1));

	gCoordinator.AddComponent<Component::com_Player>   (player, playerPlayer);
	gCoordinator.AddComponent<Component::com_Transform>(player, playerTransform);

	Create("Player", player);
}

void Stage::Update()
{
	PlayerSys->Update(&mCamera);

	RenderSys->Update(&mCamera);
}

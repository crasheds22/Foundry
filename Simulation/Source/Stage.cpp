#include "Stage.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include <cstdlib>
#include <ctime>

float RandomNumber(float min, float max)
{
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

Stage::Stage()
{
	mResources = &Resource::ResourceManager::Instance();

	srand(time(NULL));
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

	AISys = gCoordinator.RegisterSystem<System::sys_AI>();
	{
		ECS::Signature sig;
		sig.set(gCoordinator.GetComponentType<Component::com_AI>());
		sig.set(gCoordinator.GetComponentType<Component::com_Transform>());
		gCoordinator.SetSystemSignature<System::sys_AI>(sig);
	}

	AISys->Init();

	mCamera = Component::com_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//Create entities here

	for (int i = 0; i < 50; i++)
	{
		auto entity = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(entity, Component::com_Render("backpack.obj", "backpack"));
		gCoordinator.AddComponent<Component::com_Transform>(entity, Component::com_Transform(glm::vec3(RandomNumber(-100.0f, 100.0f), 0.0f, RandomNumber(-100.0f, 100.0f)), glm::vec3(0), glm::vec3(RandomNumber(0.1f, 2.0f))));

		Create("Backpack_" + std::to_string(i), entity);
	}

	auto player = gCoordinator.CreateEntity();
		Component::com_Player playerPlayer(2.5f, 0.1f);
		Component::com_Transform playerTransform(mCamera.Position(), glm::vec3(0), glm::vec3(1));

	gCoordinator.AddComponent<Component::com_Player>   (player, playerPlayer);
	gCoordinator.AddComponent<Component::com_Transform>(player, playerTransform);

	Create("Player", player);

	auto Thomas = gCoordinator.CreateEntity();
		Component::com_Transform	thomasTransform(glm::vec3(0), glm::vec3(0), glm::vec3(1));
		Component::com_AI			thomasAI(2.0f, 0.1f, thomasTransform);
		Component::com_Render		thomasRender("Thomas.obj", "thomas");

	gCoordinator.AddComponent<Component::com_AI>(Thomas, thomasAI);
	gCoordinator.AddComponent<Component::com_Transform>(Thomas, thomasTransform);
	gCoordinator.AddComponent<Component::com_Render>(Thomas, thomasRender);

	Create("Thomas", Thomas);
}

void Stage::Update()
{
	PlayerSys->Update(&mCamera);

	RenderSys->Update(&mCamera);

	AISys->Update();
}

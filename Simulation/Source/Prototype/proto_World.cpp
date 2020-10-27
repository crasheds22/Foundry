#include "Prototype/proto_World.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	World::World(std::string name)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render(name, "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, Component::com_Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1)));

	}

	World::~World()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

#include "Prototype/proto_Collider.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Collider::Collider(std::string name, Component::com_Transform transform)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);
		gCoordinator.AddComponent<Component::com_Physics>(mID, Component::com_Physics(1, 0.5, 2, 2, 2, 1, new Box(glm::vec3(-1), glm::vec3(1))));

	}

	Collider::~Collider()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

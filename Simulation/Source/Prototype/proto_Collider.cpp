#include "Prototype/proto_Collider.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Collider::Collider(std::string name, Component::com_Transform transform, glm::vec3 Max, glm::vec3 Min, int type)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

		glm::vec3 dim = Max - Min;
		Component::com_Physics physics(10.0f, 0.5f, dim.x, dim.y, dim.z, type, new Box(Max, Min));
		gCoordinator.AddComponent<Component::com_Physics>(mID, physics);
	}

	Collider::~Collider()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

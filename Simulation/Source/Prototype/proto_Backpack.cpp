#include "Prototype/proto_Backpack.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Backpack::Backpack(std::string name, Component::com_Transform transform)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("backpack", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

	}

	Backpack::~Backpack()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

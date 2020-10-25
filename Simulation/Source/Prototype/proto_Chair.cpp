#include "Prototype/proto_Chair.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Chair::Chair(std::string name, Component::com_Transform transform) 
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("chair", "model"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

	}
	
	Chair::~Chair()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

#include "Prototype/proto_Monitor.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Monitor::Monitor(std::string name, Component::com_Transform transform) 
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("monitor", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

	}
	
	Monitor::~Monitor()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

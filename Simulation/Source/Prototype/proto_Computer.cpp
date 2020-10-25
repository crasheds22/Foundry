#include "Prototype/proto_Computer.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Computer::Computer(std::string name, Component::com_Transform transform) 
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("computer", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

	}
	
	Computer::~Computer()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

#include "Prototype/proto_Table.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Table::Table(std::string name, Component::com_Transform transform) 
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("table", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

	}

	Table::~Table()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

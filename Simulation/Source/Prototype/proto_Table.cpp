#include "Prototype/proto_Table.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Table::Table(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("table", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

		Component::com_Physics physics(10.0f, 0.5f, 0.5, 1.5, 1.5f, 0, new Box(glm::vec3(-0.25, -0.75f, -0.75f), glm::vec3(0.25f, 0.75f, 0.75f)));
		gCoordinator.AddComponent<Component::com_Physics>(mID, physics);

	}

	Table::~Table()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

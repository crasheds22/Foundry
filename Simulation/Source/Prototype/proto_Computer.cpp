#include "Prototype/proto_Computer.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Computer::Computer(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("computer", "models"));
		transform.Position(transform.Position() + glm::vec3(0, 1, 0));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

		Component::com_Physics physics(10.0f, 0.5f, 0.5, 1.5, 1.5f, 0, new Box(glm::vec3(-0.25, -0.75f, -0.75f), glm::vec3(0.25f, 0.75f, 0.75f)));
		gCoordinator.AddComponent<Component::com_Physics>(mID, physics);
	}
	
	Computer::~Computer()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

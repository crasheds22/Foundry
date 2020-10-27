#include "Prototype/proto_Monitor.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Monitor::Monitor(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Render>(mID, Component::com_Render("monitor", "models"));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

		glm::vec3 dim = minMax.first - minMax.second;
		Component::com_Physics physics(10.0f, 0.5f, dim.x, dim.y, dim.z, 0, new Box(minMax.first, minMax.second));
		gCoordinator.AddComponent<Component::com_Physics>(mID, physics);


	}
	
	Monitor::~Monitor()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

#include "Prototype/proto_Player.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Player::Player(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Player>(mID, Component::com_Player(5.0f, 0.1f));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

		Props::Instance().PlayerID(mID);

		glm::vec3 dim = minMax.first - minMax.second;
		Component::com_Physics physics(70.0f, 0.5f, dim.x, dim.y, dim.z, 0, new Box(minMax.first, minMax.second));
		gCoordinator.AddComponent<Component::com_Physics>(mID, physics);

	}

	Player::~Player()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

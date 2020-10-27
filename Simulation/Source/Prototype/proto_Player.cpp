#include "Prototype/proto_Player.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace Prototype
{
	Player::Player(std::string name, Component::com_Transform transform)
		: IPrototype(name)
	{
		mID = gCoordinator.CreateEntity();

		gCoordinator.AddComponent<Component::com_Player>(mID, Component::com_Player(2.5f, 0.1f));
		gCoordinator.AddComponent<Component::com_Transform>(mID, transform);

	}

	Player::~Player()
	{
		gCoordinator.DestroyEntity(mID);
	}
}

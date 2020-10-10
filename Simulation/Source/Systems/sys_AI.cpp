#include "Systems/sys_AI.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace System
{
	void sys_AI::Init()
	{
		mFlags = { glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0) };
	}

	void sys_AI::Update()
	{
		for (auto entity : mEntities)
		{

		}
	}
}

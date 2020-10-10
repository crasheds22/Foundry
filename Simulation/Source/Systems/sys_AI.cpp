#include "Systems/sys_AI.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include "Components/com_AI.h"
#include "Components/com_Transform.h"

#include <iostream>

namespace System
{
	void sys_AI::Init()
	{
		mFlags = { glm::vec3(10, 0, 10), glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(10, 0, 0) };
	}

	void sys_AI::Update()
	{
		for (auto entity : mEntities)
		{
			auto& ai = gCoordinator.GetComponent<Component::com_AI>(entity);
			auto& transform = gCoordinator.GetComponent<Component::com_Transform>(entity);

			ai.NewTarget(mFlags[flagNo]);

			if (ai.TargetReached())
			{
				flagNo++;

				if (flagNo > 3)
					flagNo = 0;
			}

			ai.Move();

			transform.Position(ai.Position());
		}
	}
}

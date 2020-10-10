#include "Systems/sys_AI.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include "Components/com_AI.h"
#include "Components/com_Transform.h"

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
			auto& ai = gCoordinator.GetComponent<Component::com_AI>(entity);
			auto& transform = gCoordinator.GetComponent<Component::com_Transform>(entity);

			if (ai.TargetReached())
			{
				if (flagNo++ > 3)
				{
					ai.NewTarget(mFlags[0]);
					flagNo = 0;
				}
				else
				{
					ai.NewTarget(mFlags[flagNo++]);
				}
			}

			ai.Move();
		}
	}
}

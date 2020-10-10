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
	}

	void sys_AI::Update()
	{
		for (auto entity : mEntities)
		{
			auto& ai = gCoordinator.GetComponent<Component::com_AI>(entity);
			auto& transform = gCoordinator.GetComponent<Component::com_Transform>(entity);

			ai.Move(Props::Instance().DeltaTime());

			transform.Position(ai.Position());
		}
	}
}

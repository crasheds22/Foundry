#include "Systems/sys_AI.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include "Components/com_Transform.h"
#include "Components/com_AI.h"

namespace System
{
	void sys_AI::Init()
	{
	}

	void sys_AI::Update()
	{
		for (auto entity : mEntities)
		{
			auto& trans = gCoordinator.GetComponent<Component::com_Transform>(entity);
			auto& brain = gCoordinator.GetComponent<Component::com_AI>(entity);

			trans.Position(trans.Position() + trans.Front() * Props::Instance().DeltaTime() * brain.Speed());
		}
	}
}

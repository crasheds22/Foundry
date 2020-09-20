#include "Systems/sys_PlayerControl.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include "Components/com_Player.h"
#include "Components/com_Transform.h"

namespace System
{
	void sys_PlayerControl::Init()
	{
		ref = &Props::Instance();
	}

	void sys_PlayerControl::Update(Component::com_Camera* camera)
	{
		//for (auto entity : mEntities)
		//{
			//auto* camera = &gCoordinator.GetComponent<Component::com_Camera>(entity);

			float v = ref->DeltaTime() * 2.5f;

			if (ref->Pressed(Actions::Move::FORWARD))
				camera->MoveCamera(Component::Direction::FORWARD, v);
			if (ref->Pressed(Actions::Move::BACKWARD))
				camera->MoveCamera(Component::Direction::BACKWARD, v);
			if (ref->Pressed(Actions::Move::LEFT))
				camera->MoveCamera(Component::Direction::LEFT, v);
			if (ref->Pressed(Actions::Move::RIGHT))
				camera->MoveCamera(Component::Direction::RIGHT, v);

			double xOff = ref->MouseOffset().first;
			double yOff = ref->MouseOffset().second;

			camera->RotateCamera(xOff * 0.1f, yOff * 0.1f);
		//}
	}
}

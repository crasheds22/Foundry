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
		for (auto entity : mEntities)
		{
			auto& player = gCoordinator.GetComponent<Component::com_Player>(entity);
			auto& transform = gCoordinator.GetComponent<Component::com_Transform>(entity);

			float v = ref->DeltaTime() * player.MoveSpeed();

			int RL = ref->Pressed(Actions::Move::RIGHT) - ref->Pressed(Actions::Move::LEFT);
			int FB = ref->Pressed(Actions::Move::FORWARD) - ref->Pressed(Actions::Move::BACKWARD);

			glm::vec3 direction = ((camera->Front() * (float)FB) + (camera->Right() * (float)RL)) * v;

			//direction.y = 0.0f;

			transform.Front(camera->Front());

			transform.Position(transform.Position() + direction);

			double xOff = ref->MouseOffset().first * player.RotateSpeed();
			double yOff = ref->MouseOffset().second * player.RotateSpeed();

			camera->RotateCamera(xOff, yOff);

			camera->Position(transform.Position());
			transform.Rotation(camera->Rotations());
		}
	}
}

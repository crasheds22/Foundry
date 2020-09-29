#pragma once

#include "ECS/System.h"

#include "Components/com_Physics.h"
#include "Components/com_Transform.h"
#include "Components/Collider.h"

#include "Algorithms/Physics.h"
#include "Props.h"

#include <vector>

namespace System
{
	class sys_Physics : public ECS::System
	{
	public:
		void Init();

		void Update();

	private:
		std::vector<Collision> CollisionList;
		Props* ref = nullptr;
	};
}
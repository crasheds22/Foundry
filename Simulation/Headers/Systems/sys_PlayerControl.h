#pragma once

#include "ECS/System.h"

#include "Props.h"

#include "Components/com_Camera.h"

namespace System
{
	class sys_PlayerControl
		: public ECS::System
	{
	public:
		void Init();

		void Update(Component::com_Camera* camera);

	private:
		Props* ref = nullptr;
	};
}

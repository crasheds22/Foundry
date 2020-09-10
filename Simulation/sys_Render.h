#pragma once

#include "System.h"

#include "com_Camera.h"

namespace System
{
	class sys_Render : public ECS::System
	{
	public:
		void Init();

		void Update(Component::com_Camera& camera);

	private:

	};
}

#pragma once

#include "ECS/System.h"

#include "Components/com_Camera.h"

#include "Graphics/Graphics.h"

namespace System
{
	class sys_Render : public ECS::System
	{
	public:
		void Init();

		void Update(const Component::com_Camera* camera);

	private:

	};
}

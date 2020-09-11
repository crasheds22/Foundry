#pragma once

#include "System.h"

#include "com_Camera.h"

#include "Graphics.h"

namespace System
{
	class sys_Render : public ECS::System
	{
	public:
		void Init();

		void Update(const Component::com_Camera* camera, const Graphics* graphics);

	private:

	};
}

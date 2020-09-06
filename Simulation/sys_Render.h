#pragma once

#include "../ECS_core/System.h"

#include "com_Model.h"
#include "com_Shader.h"
#include "com_Transform.h"

namespace System
{
	class Render : public ECS::System
	{
	public:
		Render();

		void Update(float dt);

	private:

	};
}

#pragma once

#include "../ECS_core/System.h"
#include "../ECS_core/Coordinator.h"

#include "Model.h"
#include "Shader.h"
#include "Transform.h"

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

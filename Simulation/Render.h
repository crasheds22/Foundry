#pragma once

#include "../ECS_core/System.h"
#include "../ECS_core/Coordinator.h"

#include "../Components/Model.h"
#include "../Components/Shader.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"

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

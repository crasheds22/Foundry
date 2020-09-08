#pragma once

#include "../ECS_core/System.h"

#include "../Graphics/Graphics.h"

#include "Props.h"

#include "com_Model.h"
#include "com_Shader.h"
#include "com_Transform.h"

#include <glm/glm.hpp>

namespace System
{
	class Render : public ECS::System
	{
	public:
		Render();

		void Update();

	private:

	};
}

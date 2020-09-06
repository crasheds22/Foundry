#pragma once

#include "../ECS_core/System.h"

#include "Props.h"

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

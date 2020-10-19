#ifndef __SYS_AI_H__
#define __SYS_AI_H__

#include <cmath>
#include <cstdlib>
#include <ctime>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Props.h"

#include "ECS/System.h"

namespace System
{
	class sys_AI
		: public ECS::System
	{
	public:

		void Init();

		void Update();

	private:

	};
}

#endif

#ifndef __SYS_AI_H__
#define __SYS_AI_H__

#include "ECS/System.h"

#include "Props.h"

#include <vector>
#include <glm/vec3.hpp>

namespace System
{
	class sys_AI
		: public ECS::System
	{
	public:

		void Init();

		void Update();

	private:
		std::vector<glm::vec3> mFlags;

	};
}

#endif

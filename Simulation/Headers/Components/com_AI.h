#ifndef __COM_AI_H__
#define __COM_AI_H__

#include <glm/vec3.hpp>

namespace Component
{
	class com_AI
	{
	public:
		com_AI() {}
		com_AI(float speed);

		void Target(glm::vec3 target);
		glm::vec3 Target() const;

		float Speed() const;

	private:
		glm::vec3 mTarget;

		float mSpeed;
	};
}

#endif

#include "Components/com_AI.h"

namespace Component
{
	com_AI::com_AI(float speed)
	{
		mSpeed = speed;
		mTarget = glm::vec3(0);
	}

	void com_AI::Target(glm::vec3 target)
	{
		mTarget = target;
	}

	glm::vec3 com_AI::Target() const
	{
		return mTarget;
	}

	float com_AI::Speed() const
	{
		return mSpeed;
	}
}

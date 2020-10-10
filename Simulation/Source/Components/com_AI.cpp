#include "Components/com_AI.h"

namespace Component
{
	com_AI::com_AI(float move, float rotate, glm::vec3& position)
	{
		mSpeed = move;
		mRotate = rotate;
		mPosition = &position;
		mTarget = glm::vec3(0);
	}

	void com_AI::NewTarget(glm::vec3 target)
	{
		mTarget = target;
	}
	
	bool com_AI::TargetReached()
	{
		if (glm::length(glm::normalize(mTarget - *mPosition)) <= 1.0f)
			return true;

		return false;
	}
	
	void com_AI::Move()
	{
		glm::vec3 direction = *mPosition - mTarget;

		direction = glm::normalize(direction);

		*mPosition += direction * mSpeed;
	}
}

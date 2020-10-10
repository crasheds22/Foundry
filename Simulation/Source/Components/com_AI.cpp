#include "Components/com_AI.h"

namespace Component
{
	com_AI::com_AI(float move, float rotate, glm::vec3 position)
	{
		mSpeed = move;
		mRotate = rotate;
		mPosition = position;
		mTarget = glm::vec3(0);
	}

	void com_AI::NewTarget(glm::vec3 target)
	{
		mTarget = target;
	}
	
	bool com_AI::TargetReached()
	{
		if (glm::length(mPosition - mTarget) <= 1.0f)
			return true;

		return false;
	}
	
	void com_AI::Move(float deltaTime)
	{
		glm::vec3 direction = mTarget - mPosition;

		direction = glm::normalize(direction);

		mPosition += direction * mSpeed * deltaTime;
	}

	glm::vec3 com_AI::Position() const
	{
		return mPosition;
	}
}

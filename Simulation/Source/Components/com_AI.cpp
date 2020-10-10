#include "Components/com_AI.h"

#include <cstdlib>
#include <ctime>

namespace Component
{
	float RandomNumber(float min, float max)
	{
		return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
	}

	com_AI::com_AI(float move, float rotate, com_Transform transform)
	{
		mSpeed = move;
		mRotate = rotate;

		mTransform = transform;

		mAccumulatedTime = 0.0f;

		mTarget = glm::vec3(0);

		srand(time(NULL));
	}
	
	void com_AI::Move(float deltaTime)
	{
		mAccumulatedTime += deltaTime;

		if ((int)mAccumulatedTime %  5 == 3)
		{
			mTarget = glm::vec3(RandomNumber(-100.0f, 100.0f), 0, RandomNumber(-100.0f, 100.0f));
			mAccumulatedTime = 0.0f;
		}

		if (glm::length(mTransform.Position() - mTarget) > 1.0f)
		{
			glm::vec3 direction = mTarget - mTransform.Position();

			direction = glm::normalize(direction);

			mTransform.Position(mTransform.Position() + direction * mSpeed * deltaTime);
		}
	}

	com_Transform com_AI::Transform() const
	{
		return mTransform;
	}
}

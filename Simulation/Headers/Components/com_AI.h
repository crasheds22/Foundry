#ifndef __COM_AI_H__
#define __COM_AI_H__

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "com_Transform.h"

namespace Component
{
	class com_AI
	{
	public:
		com_AI() {};
		com_AI(float move, float rotate, com_Transform transform);

		void Move(float deltaTime);

		com_Transform Transform() const;

	private:
		glm::vec3 mTarget;

		com_Transform mTransform;

		float mAccumulatedTime;

		float mSpeed;
		float mRotate;
	};
}

#endif

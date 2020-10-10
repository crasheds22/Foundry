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
		com_AI(float move, float rotate, glm::vec3 position);

		void Move(float deltaTime);

		glm::vec3 Position() const;

	private:
		glm::vec3 mTarget;
		glm::vec3 mPosition;

		float mSpeed;
		float mRotate;
	};
}

#endif

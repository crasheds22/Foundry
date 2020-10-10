#ifndef __COM_AI_H__
#define __COM_AI_H__

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace Component
{
	class com_AI
	{
	public:
		com_AI() {};
		com_AI(float move, float rotate, glm::vec3& position);

		void NewTarget(glm::vec3 target);
		bool TargetReached();

		void Move();

	private:
		glm::vec3 mTarget;
		glm::vec3* mPosition;

		float mSpeed;
		float mRotate;
	};
}

#endif

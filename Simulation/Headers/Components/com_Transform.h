#pragma once

#include <glm/vec3.hpp>

namespace Component
{
	class com_Transform
	{
	public:
		com_Transform() {};
		com_Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

		glm::vec3 Position() const;
		void Position(glm::vec3 position);

		glm::vec3 Rotation() const;
		void Rotation(glm::vec3 rotation);

		glm::vec3 Scale() const;
		void Scale(glm::vec3 scale);

		glm::vec3 Front() const;
		void Front(glm::vec3 front);

	private:
		glm::vec3 mPosition{};
		glm::vec3 mRotation{};
		glm::vec3 mScale{};
		glm::vec3 mFront{};
	};
}

#pragma once

#include <glm/vec3.hpp>

namespace Component
{
	class Transform
	{
	public:
		Transform() {};
		Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
		Transform(const Transform& t);
		~Transform();

		glm::vec3 Position() const;
		void Position(glm::vec3 position);

		glm::vec3 Rotation() const;
		void Rotation(glm::vec3 rotation);

		glm::vec3 Scale() const;
		void Scale(glm::vec3 scale);

	private:
		glm::vec3 mPosition{};
		glm::vec3 mRotation{};
		glm::vec3 mScale{};
	};
}

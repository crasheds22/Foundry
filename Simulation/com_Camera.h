#pragma once

#include <map>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Component
{
	enum class Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

	class com_Camera
	{
	public:
		com_Camera() {};
		com_Camera(glm::vec3 pos, glm::vec3 wup = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		com_Camera(const com_Camera& c);
		~com_Camera();

		glm::vec3 Position() const;
		glm::vec3 Front() const;
		glm::vec3 Right() const;
		glm::vec3 Up() const;
		glm::vec3 WorldUp() const;

		float Yaw() const;
		float Pitch() const;
		float Roll() const;

		float Zoom() const;

		glm::mat4 ViewMatrix() const;

		void MoveCamera(Direction direction, float velocity);
		void RotateCamera(float xOffset, float yOffset, float zOffset = 0.0f, bool constrainPitch = true);
		void Zoom(float yOffset);

	private:
		glm::vec3 mPosition{};
		glm::vec3 mFront{};
		glm::vec3 mRight{};
		glm::vec3 mUp{};
		glm::vec3 mWorldUp{};

		float mYaw{};
		float mPitch{};
		float mRoll{};

		float mZoom{};

		std::map<Direction, glm::vec3> DirectionMapper{};

		void UpdateCameraVectors();
		void UpdateMapper();
	};
}

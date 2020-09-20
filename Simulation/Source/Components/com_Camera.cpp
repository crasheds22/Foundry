#include "Components/com_Camera.h"

namespace Component
{
	com_Camera::com_Camera(glm::vec3 pos, glm::vec3 wup, float yaw, float pitch)
		: mPosition(pos), mWorldUp(wup), mYaw(yaw), mPitch(pitch), mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mZoom(45.0f)
	{
		UpdateCameraVectors();
	}

	com_Camera::com_Camera(const com_Camera& c)
		: mPosition(c.mPosition), mFront(c.mFront), mRight(c.mRight), mUp(c.mUp), mYaw(c.mYaw), mPitch(c.mPitch), mRoll(c.mRoll), mZoom(c.mZoom), mWorldUp(glm::vec3(0.0f, 1.0f, 0.0f))
	{
		UpdateCameraVectors();
	}

	void com_Camera::Position(const glm::vec3 position)
	{
		mPosition = position;
	}

	glm::vec3 com_Camera::Position() const
	{
		return mPosition;
	}
	
	glm::vec3 com_Camera::Front() const
	{
		return mFront;
	}
	
	glm::vec3 com_Camera::Right() const
	{
		return mRight;
	}
	
	glm::vec3 com_Camera::Up() const
	{
		return mUp;
	}
	
	glm::vec3 com_Camera::WorldUp() const
	{
		return mWorldUp;
	}
	
	float com_Camera::Yaw() const
	{
		return mYaw;
	}
	
	float com_Camera::Pitch() const
	{
		return mPitch;
	}
	
	float com_Camera::Roll() const
	{
		return mRoll;
	}

	glm::vec3 com_Camera::Rotations() const
	{
		return glm::vec3(mPitch, mYaw, mRoll);
	}
	
	float com_Camera::Zoom() const
	{
		return mZoom;
	}
	
	glm::mat4 com_Camera::ViewMatrix() const
	{
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}
	
	void com_Camera::MoveCamera(Direction direction, float velocity)
	{
		mPosition += DirectionMapper[direction] * velocity;
	}
	
	void com_Camera::RotateCamera(float xOffset, float yOffset, float zOffset, bool constrainPitch)
	{
		mYaw += xOffset;
		mPitch += yOffset;
		mRoll += zOffset;

		if (constrainPitch)
		{
			if (mPitch > 89.0f)
				mPitch = 89.0f;

			if (mPitch < -89.0f)
				mPitch = -89.0f;
		}

		UpdateCameraVectors();
	}
	
	void com_Camera::Zoom(float yOffset)
	{
		mZoom -= yOffset;

		if (mZoom < 1.0f)
			mZoom = 1.0f;

		if (mZoom > 45.0f)
			mZoom = 45.0f;
	}
	
	void com_Camera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		front.y = sin(glm::radians(mPitch));
		front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

		mFront = glm::normalize(front);
		mRight = glm::normalize(glm::cross(mFront, mWorldUp));
		mUp = glm::normalize(glm::cross(mRight, mFront));

		UpdateMapper();
	}

	void com_Camera::UpdateMapper()
	{
		DirectionMapper = {
			{ Direction::FORWARD, mFront },
			{ Direction::BACKWARD, -mFront },
			{ Direction::RIGHT, mRight },
			{ Direction::LEFT, -mRight },
			{ Direction::UP, mUp },
			{ Direction::DOWN, -mUp }
		};
	}
}

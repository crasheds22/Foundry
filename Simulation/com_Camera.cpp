#include "com_Camera.h"

namespace Component
{
	Camera::Camera(glm::vec3 pos, glm::vec3 wup, float yaw, float pitch)
		: mPosition(pos), mWorldUp(wup), mYaw(yaw), mPitch(pitch), mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mZoom(45.0f)
	{
		UpdateCameraVectors();
	}

	Camera::Camera(const Camera& c)
		: mPosition(c.mPosition), mFront(c.mFront), mRight(c.mRight), mUp(c.mUp), mYaw(c.mYaw), mPitch(c.mPitch), mRoll(c.mRoll), mZoom(c.mZoom), mWorldUp(glm::vec3(0.0f, 1.0f, 0.0f))
	{
		UpdateCameraVectors();
	}

	Camera::~Camera()
	{
	}

	glm::vec3 Camera::Position() const
	{
		return mPosition;
	}
	
	glm::vec3 Camera::Front() const
	{
		return mFront;
	}
	
	glm::vec3 Camera::Right() const
	{
		return mRight;
	}
	
	glm::vec3 Camera::Up() const
	{
		return mUp;
	}
	
	glm::vec3 Camera::WorldUp() const
	{
		return mWorldUp;
	}
	
	float Camera::Yaw() const
	{
		return mYaw;
	}
	
	float Camera::Pitch() const
	{
		return mPitch;
	}
	
	float Camera::Roll() const
	{
		return mRoll;
	}
	
	float Camera::Zoom() const
	{
		return mZoom;
	}
	
	glm::mat4 Camera::ViewMatrix() const
	{
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}
	
	void Camera::MoveCamera(Direction direction, float velocity)
	{
		mPosition += DirectionMapper[direction] * velocity;
	}
	
	void Camera::RotateCamera(float xOffset, float yOffset, float zOffset, bool constrainPitch)
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
	
	void Camera::Zoom(float yOffset)
	{
		mZoom -= yOffset;

		if (mZoom < 1.0f)
			mZoom = 1.0f;

		if (mZoom > 45.0f)
			mZoom = 45.0f;
	}
	
	void Camera::UpdateCameraVectors()
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

	void Camera::UpdateMapper()
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

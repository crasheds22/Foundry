#include "Components/com_Transform.h"

namespace Component
{
	com_Transform::com_Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : mPosition(pos), mRotation(rot), mScale(scale)
	{
		mFront = glm::vec3(  cos(glm::radians(rot.y)) * cos(glm::radians(rot.x))
							,sin(glm::radians(rot.x))
							,sin(glm::radians(rot.y)) * cos(glm::radians(rot.x)) );
	}
	
	glm::vec3 com_Transform::Position() const
	{
		return mPosition;
	}
	
	void com_Transform::Position(glm::vec3 position)
	{
		mPosition = position;
	}
	
	glm::vec3 com_Transform::Rotation() const
	{
		return mRotation;
	}
	
	void com_Transform::Rotation(glm::vec3 rotation)
	{
		mRotation = rotation;
	}
	
	glm::vec3 com_Transform::Scale() const
	{
		return mScale;
	}
	
	void com_Transform::Scale(glm::vec3 scale)
	{
		mScale = scale;
	}

	glm::vec3 com_Transform::Front() const
	{
		return mFront;
	}

	void com_Transform::Front(glm::vec3 front)
	{
		mFront = front;
	}
	
	glm::vec3 com_Transform::Right() const
	{
		return glm::normalize(glm::cross(mFront, glm::vec3(0, 1, 0)));
	}
}

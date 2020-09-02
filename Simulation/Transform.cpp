#include "Transform.h"

namespace Component
{
	Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : mPosition(pos), mRotation(rot), mScale(scale)
	{
	}

	Transform::Transform(const Transform& t) : mPosition(t.mPosition), mRotation(t.mRotation), mScale(t.mScale)
	{
	}
	
	Transform::~Transform()
	{
	}
	
	glm::vec3 Transform::Position() const
	{
		return mPosition;
	}
	
	void Transform::Position(glm::vec3 position)
	{
		mPosition = position;
	}
	
	glm::vec3 Transform::Rotation() const
	{
		return mRotation;
	}
	
	void Transform::Rotation(glm::vec3 rotation)
	{
		mRotation = rotation;
	}
	
	glm::vec3 Transform::Scale() const
	{
		return mScale;
	}
	
	void Transform::Scale(glm::vec3 scale)
	{
		mScale = scale;
	}
}

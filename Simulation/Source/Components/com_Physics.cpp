#include "Components/com_Physics.h"

namespace Component {

	com_Physics::com_Physics(float mass, float invmass, float res, glm::vec3 com, glm::mat4 inertia)
		: mVelocity(glm::vec3(0)), mAcceleration(glm::vec3(0)), mRotationVel(glm::vec3(0)), mRotationAcc(glm::vec3(0)),
		mMass(mass), mInvMass(invmass), mRestitution(res), mCentreOfMass(com), mInertiaTensor(inertia)
	{
	}

	glm::vec3 com_Physics::Velocity() const
	{
		return mVelocity;
	}

	glm::vec3 com_Physics::Acceleration() const
	{
		return mAcceleration;
	}

	glm::vec3 com_Physics::RotationVel() const
	{
		return mRotationVel;
	}

	glm::vec3 com_Physics::RotationAcc() const
	{
		return mRotationAcc;
	}

	float com_Physics::Mass() const
	{
		return mMass;
	}

	float com_Physics::InvMass() const
	{
		return mInvMass;
	}

	float com_Physics::Restitution() const
	{
		return mRestitution;
	}

	glm::vec3 com_Physics::CentreOfMass() const
	{
		return mCentreOfMass;
	}

	glm::mat4 com_Physics::InertiaTensor() const
	{
		return mInertiaTensor;
	}
}

#include "Components/com_Physics.h"

namespace Component {

	com_Physics::com_Physics(float mass, float res, int width, int height, int depth, Collider* coll)
		: mVelocity(glm::vec3(0)), mAcceleration(glm::vec3(0)), mRotationVel(glm::vec3(0)), mRotationAcc(glm::vec3(0)),
		mMass(mass), mRestitution(res), mCollidercom(coll)
	{
		mInvMass = 1 / mass;
		mCentreOfMass = { width / 2.0, height / 2.0, depth / 2.0 };
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

	glm::mat3 com_Physics::InertiaTensor() const
	{
		return mInertiaTensor;
	}
	Collider* com_Physics::Collidercom() const
	{
		return mCollidercom;
	}
}

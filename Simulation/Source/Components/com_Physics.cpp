#include "Components/com_Physics.h"

namespace Component {

	com_Physics::com_Physics(float mass, float res, int width, int height, int depth, bool dynamic, Collider* coll)
		: mVelocity(glm::vec3(0)), mAcceleration(glm::vec3(0)), mRotationVel(glm::vec3(0)), mRotationAcc(glm::vec3(0)),
		mMass(mass), mRestitution(res), mDynamic(dynamic), mCollidercom(coll)
	{
		mInvMass = 1 / mass;
		mCentreOfMass = { width / 2.0, height / 2.0, depth / 2.0 };
		mCollidercom->SetInertia(mass);
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

	void com_Physics::Velocity(glm::vec3 vel)
	{
		mVelocity = vel;
	}

	void com_Physics::Acceleration(glm::vec3 acc)
	{
		mAcceleration = acc;
	}

	void com_Physics::RotationVel(glm::vec3 rotvel)
	{
		mRotationVel = rotvel;
	}

	void com_Physics::RotationAcc(glm::vec3 rotacc)
	{
		mRotationAcc = rotacc;
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

	Collider* com_Physics::Collidercom() const
	{
		return mCollidercom;
	}

	bool com_Physics::Dynamic() const
	{
		return mDynamic;
	}
}

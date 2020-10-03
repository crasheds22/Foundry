#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Components/com_Transform.h"
#include "Components/Collider.h"

namespace Component
{
	class com_Physics
	{
	public:
		com_Physics() {};
		com_Physics(float mass, float res, int width, int height, int depth, bool dynamic, Collider* coll);

		glm::vec3 Velocity() const;
		glm::vec3 Acceleration() const;
		glm::vec3 RotationVel() const;
		glm::vec3 RotationAcc() const;

		void Velocity(glm::vec3 vel);
		void Acceleration(glm::vec3 acc);
		void RotationVel(glm::vec3 rotvel);
		void RotationAcc(glm::vec3 rotacc);

		float Mass() const;
		float InvMass() const;
		float Restitution() const;

		glm::vec3 CentreOfMass() const;

		Collider* Collidercom() const;

		bool Dynamic() const;

	private:
		glm::vec3 mVelocity{};
		glm::vec3 mAcceleration{};
		glm::vec3 mRotationVel{};
		glm::vec3 mRotationAcc{};

		float mMass{};
		float mInvMass{};
		float mRestitution{};

		glm::vec3 mCentreOfMass{};

		Collider* mCollidercom;

		bool mDynamic;
	};
}
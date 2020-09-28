#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

namespace Component
{
	class com_Physics
	{
	public:
		com_Physics() {};
		com_Physics(float mass, float res, int width, int height, int depth);

		glm::vec3 Velocity() const;
		glm::vec3 Acceleration() const;
		glm::vec3 RotationVel() const;
		glm::vec3 RotationAcc() const;

		float Mass() const;
		float InvMass() const;
		float Restitution() const;

		glm::vec3 CentreOfMass() const;
		glm::mat3 InertiaTensor() const;

	private:
		glm::vec3 mVelocity{};
		glm::vec3 mAcceleration{};
		glm::vec3 mRotationVel{};
		glm::vec3 mRotationAcc{};

		float mMass{};
		float mInvMass{};
		float mRestitution{};

		glm::vec3 mCentreOfMass{};
		glm::mat3 mInertiaTensor{};
	};

}
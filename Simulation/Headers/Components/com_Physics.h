#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Algorithms/Physics.h"

#include "Components/com_Transform.h"

namespace Component
{
	class com_Physics
	{
	public:
		com_Physics() {};
		com_Physics( 
			float mass, float invmass, float res,
			glm::vec3 com, glm::mat4 inertia,
			glm::vec3 vel = glm::vec3(0, 0, 0),
			glm::vec3 acc = glm::vec3(0, 0, 0),
			glm::vec3 rotvel = glm::vec3(0, 0, 0),
			glm::vec3 rotacc = glm::vec3(0, 0, 0));

		com_Physics(const com_Physics& p);

		glm::vec3 Velocity() const;
		glm::vec3 Acceleration() const;
		glm::vec3 RotationVel() const;
		glm::vec3 RotationAcc() const;

		float Mass() const;
		float InvMass() const;
		float Restitution() const;

		glm::vec3 CentreOfMass() const;
		glm::mat4 InertiaTensor() const;

	private:
		glm::vec3 mVelocity{};
		glm::vec3 mAcceleration{};
		glm::vec3 mRotationVel{};
		glm::vec3 mRotationAcc{};

		float mMass{};
		float mInvMass{};
		float mRestitution{};

		glm::vec3 mCentreOfMass{};
		glm::mat4 mInertiaTensor{};
	};

}
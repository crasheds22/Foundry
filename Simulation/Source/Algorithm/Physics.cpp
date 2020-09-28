#include "Algorithms/Physics.h"

float Physics::CalculateRestitution(float resA, float resB)
{
	return -(1 + (resA - resB));
}

float Physics::CalculateVelocityDifference(glm::vec3 normal, glm::vec3 vA, glm::vec3 vB)
{
	return glm::dot(glm::normalize(normal), (vA - vB));
}

float Physics::CalculateAngleAround(glm::vec3 rotvel, float radius, glm::vec3 normal)
{
	return glm::dot(rotvel, (radius * glm::normalize(normal)));
}

float Physics::CalculateBeast(float radius, glm::vec3 normal, glm::mat3 inertia)
{
	return ((radius * glm::normalize(normal)) * (glm::inverse(inertia) * (radius * glm::normalize(normal))))[0];
}

float Physics::CalculateRadius(glm::vec3 pA, glm::vec3 pB, glm::vec3 com, glm::vec3 worldPos)
{
	glm::vec3 temp = { (pA.x + pB.x) / 2.0, (pA.y + pB.y) / 2.0, (pA.z + pB.z) / 2.0 };

	return glm::distance(com + worldPos, temp);
}

float Physics::CalculateLinearForce(float mass, float acceleration)
{
	return mass * acceleration;
}

float Physics::CalculateLinearMomentum(float mass, float fvelocity)
{
	return mass * fvelocity;
}

float Physics::CalculateLinearKineticEnergy(float mass, float fvelocity)
{
	return (mass * (fvelocity * fvelocity)) / 2.0f;
}

float Physics::CalculateLinearDisplacementV(float ivelocity, float fvelocity, float time)
{
	return (ivelocity + fvelocity) * time / 2.0f;
}

float Physics::CalculateLinearDisplacementA(float ivelocity, float acceleration, float time)
{
	return (ivelocity * time) + (acceleration * (time * time) / 2.0f);
}

float Physics::CalculateLinearFinalVelocity(float ivelocity, float acceleration, float time)
{
	return (ivelocity + acceleration * time);
}

float Physics::CalculateLinearFinalVelocitySquared(float ivelocity, float acceleration, float displacement)
{
	return (ivelocity * ivelocity) + (acceleration * displacement * 2.0f);
}

float Physics::CalculateTorque(float inertia, float acceleration)
{
	return inertia * acceleration;
}

float Physics::CalculateAngularMomentum(float inertia, float fvelocity)
{
	return inertia * fvelocity;
}

float Physics::CalculateAngularKineticEnergy(float inertia, float fvelocity)
{
	return (inertia * (fvelocity * fvelocity)) / 2.0f;
}

float Physics::CalculateAngularDisplacementV(float ivelocity, float fvelocity, float time)
{
	return (ivelocity + fvelocity) * time / 2.0f;
}

float Physics::CalculateAngularDisplacementA(float ivelocity, float acceleration, float time)
{
	return (ivelocity * time) + (acceleration * (time * time) / 2.0f);
}

float Physics::CalculateAngularFinalVelocity(float ivelocity, float acceleration, float time)
{
	return (ivelocity + acceleration * time);
}

float Physics::CalculateAngularFinalVelocitySquared(float ivelocity, float acceleration, float displacement)
{
	return (ivelocity * ivelocity) + (acceleration * displacement * 2.0f);
}

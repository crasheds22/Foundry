#include "Algorithms/Physics.h"

float Physics::CalculateRestitution(float res)
{
	return -(1 + res);
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
	//Need to figure out how transpose works.
	//return 0.0f;
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

#include "Algorithms/Physics.h"

float Physics::CalculateRestitution(float resA, float resB)
{
	return -(1 + ((resA + resB) / 2));
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

glm::vec3 Physics::CalculateCollisionVel(glm::vec3 ivelocity, float lambda, float mass, glm::vec3 normal)
{
	return ivelocity + ((lambda * glm::normalize(normal)) / mass);
}

glm::vec3 Physics::CalculateCollisionRotVel(glm::vec3 irotvel, float lambda, glm::mat3 inertia, float radius, glm::vec3 normal)
{
	return irotvel + lambda * glm::inverse(inertia) * (radius * glm::normalize(normal));
}

glm::vec3 Physics::ApplyFriction(glm::vec3 ivelocity)
{
	if (glm::length(ivelocity) > 1)
	{
		return (ivelocity -= glm::normalize(ivelocity));
	}
	else
	{
		return glm::vec3(0);
	}
}


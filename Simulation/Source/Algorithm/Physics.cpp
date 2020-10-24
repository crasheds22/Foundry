#include "Algorithms/Physics.h"

float Physics::CalculateRestitution(float resA, float resB)
{
	return -(1 + ((resA + resB) / 2.0f));
}

float Physics::CalculateVelocityDifference(glm::vec3 normal, glm::vec3 vA, glm::vec3 vB)
{
	return glm::dot(glm::normalize(normal), (vA - vB));
}

float Physics::CalculateAngleAround(glm::vec3 rotvel, glm::vec3 radius, glm::vec3 normal)
{
	return glm::dot(glm::radians(rotvel), glm::cross(radius, glm::normalize(normal)));
}

float Physics::CalculateBeast(glm::vec3 radius, glm::vec3 normal, glm::mat3 inertia)
{
	return (glm::cross(radius, glm::normalize(normal)) * (glm::inverse(inertia) * glm::cross(radius, glm::normalize(normal))))[0];
}

glm::vec3 Physics::CalculateRadius(glm::vec3 pA, glm::vec3 pB, glm::vec3 com, glm::vec3 worldPos)
{
	glm::vec3 temp = { (pA.x + pB.x) / 2.0f, (pA.y + pB.y) / 2.0f, (pA.z + pB.z) / 2.0f };

	return (temp - (com + worldPos));
}

glm::vec3 Physics::CalculateCollisionVel(glm::vec3 ivelocity, float lambda, float mass, glm::vec3 normal)
{
	return ivelocity + ((lambda * glm::normalize(normal)) / mass);
}

glm::vec3 Physics::CalculateCollisionRotVel(glm::vec3 irotvel, float lambda, glm::mat3 inertia, glm::vec3 radius, glm::vec3 normal)
{
	return glm::radians(irotvel) + lambda * glm::inverse(inertia) * glm::cross(radius, glm::normalize(normal));
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


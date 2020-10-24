#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

class Physics
{
public:
	static float CalculateRestitution(float resA, float resB);
	static float CalculateVelocityDifference(glm::vec3 normal, glm::vec3 vA, glm::vec3 vB);
	static float CalculateAngleAround(glm::vec3 rotvel, glm::vec3 radius, glm::vec3 normal);
	static float CalculateBeast(glm::vec3 radius, glm::vec3 normal, glm::mat3 inertia);
	static glm::vec3 CalculateRadius(glm::vec3 pA, glm::vec3 pB, glm::vec3 com, glm::vec3 worldPos);

	static glm::vec3 CalculateCollisionVel(glm::vec3 ivelocity, float lambda, float mass, glm::vec3 normal);
	static glm::vec3 CalculateCollisionRotVel(glm::vec3 irotvel, float lambda, glm::mat3 inertia, glm::vec3 radius, glm::vec3 normal);

	static glm::vec3 ApplyFriction(glm::vec3 ivelocity);
};


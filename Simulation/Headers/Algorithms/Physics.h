#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

class Physics
{
public:
	static float CalculateRestitution(float resA, float resB);
	static float CalculateVelocityDifference(glm::vec3 normal, glm::vec3 vA, glm::vec3 vB);
	static float CalculateAngleAround(glm::vec3 rotvel, float radius, glm::vec3 normal);
	static float CalculateBeast(float radius, glm::vec3 normal, glm::mat3 inertia);
	static float CalculateRadius(glm::vec3 pA, glm::vec3 pB, glm::vec3 com, glm::vec3 worldPos);

	static glm::vec3 CalculateCollisionVel(glm::vec3 ivelocity, float lambda, float mass, glm::vec3 normal);
	static glm::vec3 CalculateCollisionRotVel(glm::vec3 irotvel, float lambda, glm::mat3 inertia, float radius, glm::vec3 normal);

	static float CalculateLinearForce(float mass, float acceleration);
	static float CalculateLinearMomentum(float mass, float fvelocity);
	static float CalculateLinearKineticEnergy(float mass, float fvelocity);
	static float CalculateLinearDisplacementV(float ivelocity, float fvelocity, float time);
	static float CalculateLinearDisplacementA(float ivelocity, float acceleration, float time);
	static float CalculateLinearFinalVelocity(float ivelocity, float acceleration, float time);
	static float CalculateLinearFinalVelocitySquared(float ivelocity, float acceleration, float displacement);

	static float CalculateTorque(float inertia, float acceleration);
	static float CalculateAngularMomentum(float inertia, float fvelocity);
	static float CalculateAngularKineticEnergy(float inertia, float fvelocity);
	static float CalculateAngularDisplacementV(float ivelocity, float fvelocity, float time);
	static float CalculateAngularDisplacementA(float ivelocity, float acceleration, float time);
	static float CalculateAngularFinalVelocity(float ivelocity, float acceleration, float time);
	static float CalculateAngularFinalVelocitySquared(float ivelocity, float acceleration, float displacement);
};


#pragma once

#include "../ECS_core/Types.h"

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

class Physics
{
public:
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


#pragma once
#include <glm/glm.hpp>

class Physics
{
public:
	static float CalculateLinearForce(float mass, float acceleration);
	static float CalculateLinearMomentum(float mass, float fvelocity);
	static float CalculateLinearKineticEnergy(float mass, float fvelocity);
	static float CalculateLinearDisplacement(float ivelocity, float fvelocity, float time);
	static float CalculateLinearDisplacement(float ivelocity, float acceleration, float time);
	static float CalculateLinearFinalVelocity(float ivelocity, float acceleration, float time);
	static float CalculateLinearFinalVelocitySquared(float ivelocity, float acceleration, float displacement);

	static float CalculateAngularForce(float mass, float acceleration);
	static float CalculateAngularMomentum(float mass, float fvelocity);
	static float CalculateAngularKineticEnergy(float mass, float fvelocity);
	static float CalculateAngularDisplacement(float ivelocity, float fvelocity, float time);
	static float CalculateAngularDisplacement(float ivelocity, float acceleration, float time);
	static float CalculateAngularFinalVelocity(float ivelocity, float acceleration, float time);
	static float CalculateAngularFinalVelocitySquared(float ivelocity, float acceleration, float displacement);

private:
	Physics() { };
};
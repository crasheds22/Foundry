#include "Physics.h"

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

float Physics::CalculateLinearDisplacement(float ivelocity, float fvelocity, float time)
{
	return (ivelocity + fvelocity) * time / 2.0f;
}

float Physics::CalculateLinearDisplacement(float ivelocity, float acceleration, float time)
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

float Physics::CalculateAngularForce(float mass, float acceleration)
{
	return 0.0f;
}

float Physics::CalculateAngularMomentum(float mass, float fvelocity)
{
	return 0.0f;
}

float Physics::CalculateAngularKineticEnergy(float mass, float fvelocity)
{
	return 0.0f;
}

float Physics::CalculateAngularDisplacement(float ivelocity, float fvelocity, float time)
{
	return 0.0f;
}

float Physics::CalculateAngularDisplacement(float ivelocity, float acceleration, float time)
{
	return 0.0f;
}

float Physics::CalculateAngularFinalVelocity(float ivelocity, float acceleration, float time)
{
	return 0.0f;
}

float Physics::CalculateAngularFinalVelocitySquared(float ivelocity, float acceleration, float displacement)
{
	return 0.0f;
}


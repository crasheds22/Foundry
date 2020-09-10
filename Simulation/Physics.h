#pragma once

#include "../ECS_core/Types.h"

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

class CollisionPoint
{
public:
	CollisionPoint(glm::vec3 a, glm::vec3 b, bool hasCollided);

	glm::vec3 PointA() const;
	glm::vec3 PointB() const;

	glm::vec3 Normal() const;
	float Depth() const;
	bool HasCollision() const;

private:
	glm::vec3 mA;
	glm::vec3 mB;
	glm::vec3 mNormal; //B - A
	float mDepth; // mNormal.Length
	bool mHasCollision;
};

class Collision
{
public:
	Collision(ECS::Entity* A, ECS::Entity* B, CollisionPoint point);

	ECS::Entity* EntityA() const;
	ECS::Entity* EntityB() const;

	CollisionPoint Point() const;

private:
	ECS::Entity* mEntityA;
	ECS::Entity* mEntityB;
	CollisionPoint mPoint;
};

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


#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

class CollisionPoint
{
public:
	CollisionPoint(glm::vec3 a, glm::vec3 b, bool hasCollided);

	glm::vec3 PointA() const;
	glm::vec3 PointB() const;
	glm::vec3 Normal() const;

	void PointA(glm::vec3 a);
	void PointB(glm::vec3 b);
	void Normal(glm::vec3 n);

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
	Collision(ECS::Entity A, ECS::Entity B, CollisionPoint point);

	ECS::Entity EntityA() const;
	ECS::Entity EntityB() const;

	CollisionPoint Point() const;

private:
	ECS::Entity mEntityA;
	ECS::Entity mEntityB;
	CollisionPoint mPoint;
};


class Box;
class Sphere;

class Collider
{
public:
	Collider() {};

	glm::mat3 Inertia();

	virtual CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Collider* colliderB,
		const Component::com_Transform* transformB) const = 0;

	virtual CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Box* colliderB,
		const Component::com_Transform* transformB) const = 0;
		
	virtual CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Sphere* colliderB,
		const Component::com_Transform* transformB) const = 0;

	virtual void SetInertia(float mass) = 0;

protected:
	glm::mat3 mInertia;
};

class Box : public Collider
{
public:
	Box() {};
	Box(glm::vec3 min, glm::vec3 max);

	glm::vec3 Max() const;
	glm::vec3 Min() const;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Collider* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Box* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Sphere* colliderB,
		const Component::com_Transform* transformB) const override;

	void SetInertia(float mass) override;
		
private:
	glm::vec3 mMin;
	glm::vec3 mMax;
};

class Sphere : public Collider
{
public:
	Sphere() {};
	Sphere(glm::vec3 center, float rad);

	glm::vec3 Center() const;
	float Radius() const;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Collider* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Box* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Sphere* colliderB,
		const Component::com_Transform* transformB) const override;

	void SetInertia(float mass) override;

private:
	glm::vec3 mCenter;
	float mRadius;
};
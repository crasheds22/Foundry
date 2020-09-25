#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Algorithms/Physics.h"

#include "Components/com_Transform.h"

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

namespace Component
{
	class com_Box;
	class com_Sphere;
	class com_Plane;

	class com_Collider
	{
	public:
		com_Collider() {};

		virtual CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Collider* colliderB,
			const com_Transform* transformB) const = 0;

		virtual CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Box* colliderB,
			const com_Transform* transformB) const = 0;		
		
		virtual CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Sphere* colliderB,
			const com_Transform* transformB) const = 0;		
		
		virtual CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Plane* colliderB,
			const com_Transform* transformB) const = 0;

	private:

	};

	class com_Box : public com_Collider
	{
	public:
		com_Box() {};
		com_Box(glm::vec3 min, glm::vec3 max);

		glm::vec3 Max() const;
		glm::vec3 Min() const;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Collider* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Box* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Sphere* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Plane* colliderB,
			const com_Transform* transformB) const override;
		
	private:
		glm::vec3 mMin;
		glm::vec3 mMax;
	};

	class com_Sphere : public com_Collider
	{
	public:
		com_Sphere() {};
		com_Sphere(glm::vec3 center, float rad);

		glm::vec3 Center() const;
		float Radius() const;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Collider* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Box* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Sphere* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Plane* colliderB,
			const com_Transform* transformB) const override;

	private:
		glm::vec3 mCenter;
		float mRadius;
	};

	class com_Plane : public com_Collider
	{
	public:
		com_Plane() {};
		com_Plane(glm::vec3 p, float d);

		glm::vec3 P() const;
		float D() const;
		
		float X() const;
		float Y() const;
		float Z() const;

		float Distance() const;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Collider* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Box* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Sphere* colliderB,
			const com_Transform* transformB) const override;

		CollisionPoint TestCollision(
			const com_Transform* transformA,
			const com_Plane* colliderB,
			const com_Transform* transformB) const override;

	private:
		glm::vec3 mP;
		float mD;
	};
}
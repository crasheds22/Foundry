#include "Components/Collider.h"

#include "Algorithms/CollisionAlgo.h"
#include <iostream>

CollisionPoint::CollisionPoint(glm::vec3 a, glm::vec3 b, bool hasCollided)
	: mA(a), mB(b), mNormal(glm::normalize(mB - mA)), mDepth(glm::length(mB - mA)), mHasCollision(hasCollided)
{
}

glm::vec3 CollisionPoint::PointA() const
{
	return mA;
}

glm::vec3 CollisionPoint::PointB() const
{
	return mB;
}

glm::vec3 CollisionPoint::Normal() const
{
	return mNormal;
}

void CollisionPoint::PointA(glm::vec3 a)
{
	mA = a;
}

void CollisionPoint::PointB(glm::vec3 b)
{
	mB = b;
}

void CollisionPoint::Normal(glm::vec3 n)
{
	mNormal = n;
}

float CollisionPoint::Depth() const
{
	return mDepth;
}

bool CollisionPoint::HasCollision() const
{
	return mHasCollision;
}

Collision::Collision(ECS::Entity A, ECS::Entity B, CollisionPoint point)
	: mEntityA(A), mEntityB(B), mPoint(point)
{
}

ECS::Entity Collision::EntityA() const
{
	return mEntityA;
}

ECS::Entity Collision::EntityB() const
{
	return mEntityB;
}

CollisionPoint Collision::Point() const
{
	return mPoint;
}

glm::mat3 Collider::Inertia()
{
	return mInertia;
}

//BOX=========================================================================================


Box::Box(glm::vec3 min, glm::vec3 max) : mMin(min), mMax(max)
{
}
	
glm::vec3 Box::Max() const
{
	return mMax;
}
	
glm::vec3 Box::Min() const
{
	return mMin;
}

CollisionPoint Box::TestCollision(const Component::com_Transform* transformA, const Collider* colliderB, const Component::com_Transform* transformB) const
{
	return colliderB->TestCollision(transformB, this, transformA);
}

CollisionPoint Box::TestCollision(const Component::com_Transform* transformA, const Box* colliderB, const Component::com_Transform* transformB) const
{
	return CollisionAlgo::FindBoxBox(this, transformA, colliderB, transformB);
}

CollisionPoint Box::TestCollision(const Component::com_Transform* transformA, const Sphere* colliderB, const Component::com_Transform* transformB) const
{
	CollisionPoint points = colliderB->TestCollision(transformB, this, transformA);

	glm::vec3 T = points.PointA();
	points.PointA(points.PointB());
	points.PointB(T);
	points.Normal(-points.Normal());

	return points;
}

void Box::SetInertia(float mass)
{
	float height = mMax.y - mMin.y;
	float width = mMax.x - mMin.x;
	float depth = mMax.z - mMin.z;

	float Ixx = (1.0f / 12.0f) * mass * (height * height + depth * depth);
	float Iyy = (1.0f / 12.0f) * mass * (width * width + depth * depth);
	float Izz = (1.0f / 12.0f) * mass * (width * width + height * height);

	mInertia[0][0] = Ixx;
	mInertia[1][1] = Iyy;
	mInertia[2][2] = Izz;

	std::cout << mInertia[0][0] << " " << mInertia[1][1] << " " << mInertia[2][2] << "\n" ;
}


//SPHERE=========================================================================================


Sphere::Sphere(glm::vec3 center, float rad) : mCenter(center), mRadius(rad)
{
}
	
glm::vec3 Sphere::Center() const
{
	return mCenter;
}
	
float Sphere::Radius() const
{
	return mRadius;
}

CollisionPoint Sphere::TestCollision(const Component::com_Transform* transformA, const Collider* colliderB, const Component::com_Transform* transformB) const
{
	return colliderB->TestCollision(transformA, this, transformB);
}

CollisionPoint Sphere::TestCollision(const Component::com_Transform* transformA, const Box* colliderB, const Component::com_Transform* transformB) const
{
	return CollisionAlgo::FindSphereBox(this, transformA, colliderB, transformB);
}

CollisionPoint Sphere::TestCollision(const Component::com_Transform* transformA, const Sphere* colliderB, const Component::com_Transform* transformB) const
{
	return CollisionAlgo::FindSphereSphere(this, transformA, colliderB, transformB);
}

void Sphere::SetInertia(float mass)
{
	float MoI = (2 / 5) * mass * mRadius * mRadius;

	mInertia[0][0] = MoI;
	mInertia[1][1] = MoI;
	mInertia[2][2] = MoI;
}


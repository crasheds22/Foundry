#include "Components/com_Collider.h"

#include "Algorithms/CollisionAlgo.h"

CollisionPoint::CollisionPoint(glm::vec3 a, glm::vec3 b, bool hasCollided)
	: mA(a), mB(b), mNormal(glm::normalize(mB - mA)), mDepth(glm::length(glm::normalize(mB - mA))), mHasCollision(hasCollided)
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

namespace Component
{
	//BOX=========================================================================================


	com_Box::com_Box(glm::vec3 min, glm::vec3 max) : mMin(min), mMax(max)
	{
	}
	
	glm::vec3 com_Box::Max() const
	{
		return mMax;
	}
	
	glm::vec3 com_Box::Min() const
	{
		return mMin;
	}

	CollisionPoint com_Box::TestCollision(const com_Transform* transformA, const com_Collider* colliderB, const com_Transform* transformB) const
	{
		return colliderB->TestCollision(transformB, this, transformA);
	}

	CollisionPoint com_Box::TestCollision(const com_Transform* transformA, const com_Box* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindBoxBox(this, transformA, colliderB, transformB);
	}

	CollisionPoint com_Box::TestCollision(const com_Transform* transformA, const com_Sphere* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindSphereBox(colliderB, transformA, this, transformB);
	}

	CollisionPoint com_Box::TestCollision(const com_Transform* transformA, const com_Plane* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindBoxPlane(this, transformA, colliderB, transformB);
	}


	//SPHERE=========================================================================================


	com_Sphere::com_Sphere(glm::vec3 center, float rad) : mCenter(center), mRadius(rad)
	{
	}
	
	glm::vec3 com_Sphere::Center() const
	{
		return mCenter;
	}
	
	float com_Sphere::Radius() const
	{
		return mRadius;
	}

	CollisionPoint com_Sphere::TestCollision(const com_Transform* transformA, const com_Collider* colliderB, const com_Transform* transformB) const
	{
		return colliderB->TestCollision(transformA, this, transformB);
	}

	CollisionPoint com_Sphere::TestCollision(const com_Transform* transformA, const com_Box* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindSphereBox(this, transformA, colliderB, transformB);
	}

	CollisionPoint com_Sphere::TestCollision(const com_Transform* transformA, const com_Sphere* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindSphereSphere(this, transformA, colliderB, transformB);
	}

	CollisionPoint com_Sphere::TestCollision(const com_Transform* transformA, const com_Plane* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindSpherePlane(this, transformA, colliderB, transformB);
	}
	

	//PLANE=========================================================================================


	com_Plane::com_Plane(glm::vec3 p, float d) : mP(p), mD(d)
	{
	} // end Plane

	glm::vec3 com_Plane::P() const
	{
		return mP;
	}

	float com_Plane::D() const
	{
		return mD;
	}

	float com_Plane::X() const
	{
		return -mD / mP.x;
	}

	float com_Plane::Y() const
	{
		return -mD / mP.y;
	}

	float com_Plane::Z() const
	{
		return -mD / mP.z;
	}

	float com_Plane::Distance() const
	{
		return mD / mP.length();
	}

	CollisionPoint com_Plane::TestCollision(const com_Transform* transformA, const com_Collider* colliderB, const com_Transform* transformB) const
	{
		return colliderB->TestCollision(transformA, this, transformB);
	}

	CollisionPoint com_Plane::TestCollision(const com_Transform* transformA, const com_Box* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindBoxPlane(colliderB, transformB, this, transformA);
	}

	CollisionPoint com_Plane::TestCollision(const com_Transform* transformA, const com_Sphere* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindSpherePlane(colliderB, transformB, this, transformA);
	}

	CollisionPoint com_Plane::TestCollision(const com_Transform* transformA, const com_Plane* colliderB, const com_Transform* transformB) const
	{
		return CollisionAlgo::FindPlanePlane(this, transformA, colliderB, transformB);
	}
}

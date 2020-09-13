#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include "Components/com_Collider.h"

class CollisionAlgo
{
public:
	static CollisionPoint FindSphereSphere(
		const Component::com_Sphere* sA, const Component::com_Transform* tA,
		const Component::com_Sphere* sB, const Component::com_Transform* tB);
	static CollisionPoint FindSphereBox(
		const Component::com_Sphere* sA, const Component::com_Transform* tA,
		const Component::com_Box* bB,	 const Component::com_Transform* tB);
	static CollisionPoint FindSpherePlane(
		const Component::com_Sphere* sA, const Component::com_Transform* tA,
		const Component::com_Plane* pB,	 const Component::com_Transform* tB);

	static CollisionPoint FindBoxBox(
		const Component::com_Box* bA, const Component::com_Transform* tA,
		const Component::com_Box* bB, const Component::com_Transform* tB);
	static CollisionPoint FindBoxPlane(
		const Component::com_Box* bA,	const Component::com_Transform* tA,
		const Component::com_Plane* pB, const Component::com_Transform* tB);

	static CollisionPoint FindPlanePlane(
		const Component::com_Plane* pA, const Component::com_Transform* tA,
		const Component::com_Plane* pB, const Component::com_Transform* tB);
};


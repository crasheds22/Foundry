#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include "Components/Collider.h"

class CollisionAlgo
{
public:
	static CollisionPoint FindSphereSphere(
		const Sphere* sA, const Component::com_Transform* tA,
		const Sphere* sB, const Component::com_Transform* tB);
	static CollisionPoint FindSphereBox(
		const Sphere* sA, const Component::com_Transform* tA,
		const Box* bB,	 const Component::com_Transform* tB);
	static CollisionPoint FindBoxBox(
		const Box* bA, const Component::com_Transform* tA,
		const Box* bB, const Component::com_Transform* tB);
	
private:
	static glm::vec3 ClampAABB(glm::vec3 point, glm::vec3 max, glm::vec3 min);
};


#include "CollisionAlgo.h"

CollisionPoint CollisionAlgo::FindSphereSphere(const Component::com_Sphere* sA, const Component::com_Transform* tA, const Component::com_Sphere* sB, const Component::com_Transform* tB)
{
	glm::vec3 A = sA->Center() + tA->Position();
	glm::vec3 B = sB->Center() + tB->Position();

	float Ar = sA->Radius() * tA->Scale().length();
	float Br = sB->Radius() * tB->Scale().length();

	glm::vec3 AtoB = B - A;
	glm::vec3 BtoA = A - B;

	if(AtoB.length() > Ar + Br)
	{
		return CollisionPoint(A, B, false);
	}

	A += glm::normalize(AtoB) * Ar;
	B += glm::normalize(BtoA) * Br;

	return CollisionPoint(A, B, true);
}

CollisionPoint CollisionAlgo::FindSphereBox(const Component::com_Sphere* sA, const Component::com_Transform* tA, const Component::com_Box* bB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

CollisionPoint CollisionAlgo::FindSpherePlane(const Component::com_Sphere* sA, const Component::com_Transform* tA, const Component::com_Plane* pB, const Component::com_Transform* tB)
{
	glm::vec3 A = sA->Center() + tA->Position();
	float Ar = sA->Radius() * tA->Scale().length();

	glm::vec3 N = pB->P() * tB->Rotation();
	N = glm::normalize(N);

	glm::vec3 P = N * pB->D() + tB->Position();

	float d = glm::dot((A - P), N);

	if (d > Ar)
		return CollisionPoint(A, (A - N * d), false);

	glm::vec3 B = A - N * d;
			  A = A - N * Ar;

	return CollisionPoint(A, B, true);
}

CollisionPoint CollisionAlgo::FindBoxBox(const Component::com_Box* bA, const Component::com_Transform* tA, const Component::com_Box* bB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

CollisionPoint CollisionAlgo::FindBoxPlane(const Component::com_Box* bA, const Component::com_Transform* tA, const Component::com_Plane* pB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

CollisionPoint CollisionAlgo::FindPlanePlane(const Component::com_Plane* pA, const Component::com_Transform* tA, const Component::com_Plane* pB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

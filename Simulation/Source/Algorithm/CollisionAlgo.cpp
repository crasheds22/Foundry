#include "Algorithms/CollisionAlgo.h"

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
	glm::vec3 Amin = bA->Min() * tA->Scale() + tA->Position();
	glm::vec3 Amax = bA->Max() * tA->Scale() + tA->Position();

	glm::vec3 Bmin = bB->Min() * tB->Scale() + tB->Position();
	glm::vec3 Bmax = bB->Max() * tB->Scale() + tB->Position();

	glm::vec3 Acenter = { (Amin.x + Amax.x) / 2, (Amin.y + Amax.y) / 2, (Amin.z + Amax.z) / 2 };
	glm::vec3 Bcenter = { (Amin.x + Amax.x) / 2, (Amin.y + Amax.y) / 2, (Amin.z + Amax.z) / 2 };

	glm::vec3 A = Acenter;
	glm::vec3 B = Bcenter;
	if (A.x > Bmax.x) {
		A.x = Bmax.x;
	}
	else if (A.x < Bmin.x) {
		A.x = Bmin.x;
	}
	else {
		//Nothing
	}
	//REDO FOR EVERY POINT IN A AND IN B

	if (
		!(Amin.x <= Bmax.x && Amax.x >= Bmin.x) &&
		(Amin.y <= Bmax.y && Amax.y >= Bmin.y) &&
		(Amin.z <= Bmax.z && Amax.z >= Bmin.z)
		) {
		return CollisionPoint(A, B, false);
	}


	return CollisionPoint(A, B, true);
}

CollisionPoint CollisionAlgo::FindBoxPlane(const Component::com_Box* bA, const Component::com_Transform* tA, const Component::com_Plane* pB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

CollisionPoint CollisionAlgo::FindPlanePlane(const Component::com_Plane* pA, const Component::com_Transform* tA, const Component::com_Plane* pB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

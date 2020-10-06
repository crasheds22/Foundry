#include "Algorithms/CollisionAlgo.h"

CollisionPoint CollisionAlgo::FindSphereSphere(const Sphere* sA, const Component::com_Transform* tA, const Sphere* sB, const Component::com_Transform* tB)
{
	glm::vec3 A = sA->Center() + tA->Position();
	glm::vec3 B = sB->Center() + tB->Position();

	float Ar = sA->Radius();
	float Br = sB->Radius();

	glm::vec3 AtoB = B - A;
	glm::vec3 BtoA = A - B;

	if(glm::length(AtoB) > Ar + Br)
	{
		return CollisionPoint(A, B, false);
	}

	A += glm::normalize(AtoB) * Ar;
	B += glm::normalize(BtoA) * Br;

	return CollisionPoint(A, B, true);
}

CollisionPoint CollisionAlgo::FindSphereBox(const Sphere* sA, const Component::com_Transform* tA, const Box* bB, const Component::com_Transform* tB)
{
	glm::vec3 A = sA->Center() + tA->Position();
	float Ar = sA->Radius();
	
	glm::vec3 Bmin = bB->Min() + tB->Position();
	glm::vec3 Bmax = bB->Max() + tB->Position();
	glm::vec3 Bcenter = { (Bmin.x + Bmax.x) / 2, (Bmin.y + Bmax.y) / 2, (Bmin.z + Bmax.z) / 2 };

	glm::vec3 B = ClampAABB(A, Bmax, Bmin);

	float distance = (B.x - A.x) * (B.x - A.x) +
				     (B.y - A.y) * (B.y - A.y) +
					 (B.z - A.z) * (B.z - A.z);

	glm::vec3 AtoB = Bcenter - A;

	A += glm::normalize(AtoB) * Ar;

	if (!distance < Ar * Ar) {
		return CollisionPoint(A, B, false);
	}

	return CollisionPoint(A, B, true);
}

CollisionPoint CollisionAlgo::FindSpherePlane(const Sphere* sA, const Component::com_Transform* tA, const Plane* pB, const Component::com_Transform* tB)
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

CollisionPoint CollisionAlgo::FindBoxBox(const Box* bA, const Component::com_Transform* tA, const Box* bB, const Component::com_Transform* tB)
{
	glm::vec3 Amin = bA->Min() + tA->Position();
	glm::vec3 Amax = bA->Max() + tA->Position();

	glm::vec3 Bmin = bB->Min() + tB->Position();
	glm::vec3 Bmax = bB->Max() + tB->Position();

	glm::vec3 Acenter = { (Amin.x + Amax.x) / 2, (Amin.y + Amax.y) / 2, (Amin.z + Amax.z) / 2 };
	glm::vec3 Bcenter = { (Bmin.x + Bmax.x) / 2, (Bmin.y + Bmax.y) / 2, (Bmin.z + Bmax.z) / 2 };

	glm::vec3 A = ClampAABB(Bcenter, Amax, Amin);
	glm::vec3 B = ClampAABB(Acenter, Bmax, Bmin);
	
	if (
		!(Amin.x <= Bmax.x && Amax.x >= Bmin.x) &&
		(Amin.y <= Bmax.y && Amax.y >= Bmin.y) &&
		(Amin.z <= Bmax.z && Amax.z >= Bmin.z)
		) {
		return CollisionPoint(A, B, false);
	}

	return CollisionPoint(A, B, true);
}

CollisionPoint CollisionAlgo::FindBoxPlane(const Box* bA, const Component::com_Transform* tA, const Plane* pB, const Component::com_Transform* tB)
{
	glm::vec3 Amin = bA->Min() + tA->Position();
	glm::vec3 Amax = bA->Max() + tA->Position();
	glm::vec3 Acenter = { (Amin.x + Amax.x) / 2, (Amin.y + Amax.y) / 2, (Amin.z + Amax.z) / 2 };

	glm::vec3 N = pB->P() * tB->Rotation();
	N = glm::normalize(N);

	glm::vec3 P = N * pB->D() + tB->Position();



	//Actually do this please

	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

CollisionPoint CollisionAlgo::FindPlanePlane(const Plane* pA, const Component::com_Transform* tA, const Plane* pB, const Component::com_Transform* tB)
{
	return CollisionPoint(glm::vec3(0), glm::vec3(0), false);
}

glm::vec3 CollisionAlgo::ClampAABB(glm::vec3 point, glm::vec3 max, glm::vec3 min)
{
	glm::vec3 result;

	//x coordinate clamping=============================

	if (point.x > max.x) {
		result.x = max.x;
	}
	else if (point.x < min.x) {
		result.x = min.x;
	}
	else {
		result.x = point.x;
	}

	//y coordinate clamping=============================

	if (point.y > max.y) {
		result.y = max.y;
	}
	else if (point.y < min.y) {
		result.y = min.y;
	}
	else {
		result.y = point.y;
	}

	//z coordinate clamping=============================

	if (point.z > max.z) {
		result.z = max.z;
	}
	else if (point.z < min.z) {
		result.z = min.z;
	}
	else {
		result.z = point.z;
	}

	return result;
}

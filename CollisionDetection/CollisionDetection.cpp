#include "CollisionDetection.h"

#include "../ECS_core/Coordinator.h"
//extern Coordinator gCoordinator;

float CollisionDetection::Squaref(float f) 
{
	return f * f;
} // end Squaref

bool CollisionDetection::BoxCollision(Component::Box &a, Component::Box &b) 
{
	if (a.Min().x <= b.Max().x && a.Max().x >= b.Min().x &&
		a.Min().y <= b.Max().y && a.Max().y >= b.Min().y &&
		a.Min().z <= b.Max().z && a.Max().z >= b.Min().z) {
		return true;
	} // end if

	return false;
} // end BoxCollision

bool CollisionDetection::SphereCollision(Component::Sphere &a, Component::Sphere &b) 
{
	float distance = sqrtf(Squaref(a.center.x * b.center.x) +
							Squaref(a.center.y * b.center.y) +
							Squaref(a.center.z * b.center.z));

	return distance < (a.radius + b.radius);
} // end SphereCollision

bool CollisionDetection::BoxSphereCollision(Component::Box &b, Component::Sphere &s) 
{
	float x = glm::max(b.Min().x, glm::min(s.center.x, b.Max().x));
	float y = glm::max(b.Min().y, glm::min(s.center.y, b.Max().y));
	float z = glm::max(b.Min().z, glm::min(s.center.z, b.Max().z));

	float distance = sqrtf(Squaref(x - s.center.x) +
						   Squaref(y - s.center.y) +
						   Squaref(z - s.center.z));

	return distance < Squaref(s.radius);
} // end BoxSphereCollision
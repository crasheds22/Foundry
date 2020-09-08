#include "sys_CollisionDetection.h"

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
	float distance = sqrtf(Squaref(a.Center().x * b.Center().x) +
						   Squaref(a.Center().y * b.Center().y) +
						   Squaref(a.Center().z * b.Center().z));

	return distance < (a.Radius() + b.Radius());
} // end SphereCollision

bool CollisionDetection::BoxSphereCollision(Component::Box &b, Component::Sphere &s) 
{
	float x = glm::max(b.Min().x, glm::min(s.Center().x, b.Max().x));
	float y = glm::max(b.Min().y, glm::min(s.Center().y, b.Max().y));
	float z = glm::max(b.Min().z, glm::min(s.Center().z, b.Max().z));

	float distance = sqrtf(Squaref(x - s.Center().x) +
						   Squaref(y - s.Center().y) +
						   Squaref(z - s.Center().z));

	return distance < Squaref(s.Radius());
} // end BoxSphereCollision

bool CollisionDetection::TestCollision(Component::Collider& a, Component::Collider& b) {
	if ((a.Type() == Component::ColliderType::BOX) && (b.Type() == Component::ColliderType::BOX)) {
		return BoxCollision(static_cast<Component::Box>(a), static_cast<Component::Box>(b));
	}


	return false;
}
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
	float distance = sqrtf(Squaref(a.Centre().x * b.Centre().x) +
						   Squaref(a.Centre().y * b.Centre().y) +
						   Squaref(a.Centre().z * b.Centre().z));

	return distance < (a.Radius() + b.Radius());
} // end SphereCollision

bool CollisionDetection::BoxSphereCollision(Component::Box &b, Component::Sphere &s) 
{
	float x = glm::max(b.Min().x, glm::min(s.Centre().x, b.Max().x));
	float y = glm::max(b.Min().y, glm::min(s.Centre().y, b.Max().y));
	float z = glm::max(b.Min().z, glm::min(s.Centre().z, b.Max().z));

	float distance = sqrtf(Squaref(x - s.Centre().x) +
						   Squaref(y - s.Centre().y) +
						   Squaref(z - s.Centre().z));

	return distance < Squaref(s.Radius());
} // end BoxSphereCollision
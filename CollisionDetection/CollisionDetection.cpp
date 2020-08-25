#include "CollisionDetection.h"

float CollisionDetection::Squaref(float f) {
	return f * f;
} // end Squaref

bool CollisionDetection::BoxCollision(Component::Box &a, Component::Box &b) {
	if (a.min.x <= b.max.x && a.max.x >= b.min.x &&
		a.min.y <= b.max.y && a.max.y >= b.min.y &&
		a.min.z <= b.max.z && a.min.z >= b.max.z) {
		return true;
	} // end if

	return false;
} // end BoxCollision

bool CollisionDetection::SphereCollision(Component::Sphere &a, Component::Sphere &b) {
	float distance;
	distance = sqrtf(Squaref(a.center.x * b.center.x) +
					 Squaref(a.center.y * b.center.y) +
					 Squaref(a.center.z * b.center.z));

	if (distance < (a.radius + b.radius)) {
		return true;
	} // end if

	return false;
} // end SphereCollision

bool CollisionDetection::BoxSphereCollision(Component::Box &b, Component::Sphere &s) {
	float x = glm::max(b.min.x, glm::min(s.center.x, b.max.x));
	float y = glm::max(b.min.y, glm::min(s.center.y, b.max.y));
	float z = glm::max(b.min.z, glm::min(s.center.z, b.max.z));

	float distance = sqrtf(Squaref(x - s.center.x) +
						   Squaref(y - s.center.y) +
						   Squaref(z - s.center.z));

	if (distance < Squaref(s.radius)) {
		return true;
	} // end if

	return false;
} // end BoxSphereCollision
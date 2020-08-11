#include "CollisionDetection.h"

float CollisionDetection::Squaref(float f) {
	return f * f;
} // end Squaref

bool CollisionDetection::BoxCollision(Box &a, Box &b) {
	if (a.max.x >= b.min.x && a.min.x <= b.max.x &&
		a.max.y >= b.min.y && a.min.y <= b.max.y &&
		a.max.z >= b.min.z && a.min.z <= b.max.z) {
		return true;
	} // end if

	return false;
} // end BoxCollision

bool CollisionDetection::SphereCollision(Sphere &a, Sphere &b) {
	float distance = sqrtf(Squaref(b.center.x - a.center.x) + Squaref(b.center.y - a.center.y) + Squaref(b.center.z - a.center.z));

	if ((a.radius + b.radius) > distance) {
		return true;
	} // end if

	return false;
} // end SphereCollision

bool CollisionDetection::BoxSphereCollision(Box &b, Sphere &s) {
	float distance = 0.0f;

	// I'm not entirely sure how this formula works (or if I've even implemented it correctly)
	for (int i = 0; i < 3; i++) {
		if (s.center[i] < b.min[i]) {
			distance += Squaref(s.center[i] - b.min[i]);
		} // end if
		else if (s.center[i] > b.max[i]) {
			distance += Squaref(s.center[i] - b.max[i]);
		} // end else
	} // end for

	if (distance <= Squaref(s.radius)) {
		return true;
	} // end if

	return false;
} // end BoxSphereCollision
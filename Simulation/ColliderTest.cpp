#include "ColliderTest.h"

bool ColliderTest::BoxBox() {
	Component::com_Box *a = new Component::com_Box();
	Component::com_Transform *aT = new Component::com_Transform();
	Component::com_Box *b = new Component::com_Box();
	Component::com_Transform *bT = new Component::com_Transform();

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move two boxes towards eachother until collision occurs
	} // end while

	return true;
} // end BoxBox

bool ColliderTest::SphereSphere() {
	Component::com_Sphere* a = new Component::com_Sphere();
	Component::com_Transform* aT = new Component::com_Transform();
	Component::com_Sphere* b = new Component::com_Sphere();
	Component::com_Transform* bT = new Component::com_Transform();

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move two spheres towards eachother until collision occurs
	} // end while

	return true;
} // end SphereSphere

bool ColliderTest::BoxSphere() {
	Component::com_Box* a = new Component::com_Box();
	Component::com_Transform* aT = new Component::com_Transform();
	Component::com_Sphere* b = new Component::com_Sphere();
	Component::com_Transform* bT = new Component::com_Transform();

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move a box and a sphere towards eachother until collision occurs
	} // end while

	return true;
} // end BoxSphere

bool ColliderTest::BoxPlane() {
	Component::com_Box* a = new Component::com_Box();
	Component::com_Transform* aT = new Component::com_Transform();
	Component::com_Plane* b = new Component::com_Plane();
	Component::com_Transform* bT = new Component::com_Transform();

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move a box towards a plane until collision occurs
	} // end while

	return true;
} // end BoxPlane

bool ColliderTest::SpherePlane() {
	Component::com_Sphere* a = new Component::com_Sphere();
	Component::com_Transform* aT = new Component::com_Transform();
	Component::com_Plane* b = new Component::com_Plane();
	Component::com_Transform* bT = new Component::com_Transform();

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move a sphere towards a plane until collision occurs
	} // end while

	return true;
} // end SpherePlane

bool ColliderTest::Test() {
	bool pass = false;

	pass = BoxBox();
	pass = SphereSphere();
	pass = BoxSphere();
	pass = BoxPlane();
	pass = SpherePlane();

	return pass;
} // end Test
#include "ColliderTest.h"

bool ColliderTest::BoxBox() {
	// initial positions
	glm::vec3 initPosA = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 initPosB = glm::vec3(10.0f, 0.0f, 0.0f);
	// object a
	Component::com_Box *a = new Component::com_Box(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 posA = initPosA; // position of object a
	Component::com_Transform *aT = new Component::com_Transform(posA, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	// object b
	Component::com_Box *b = new Component::com_Box(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 posB = initPosB; // position of object b
	Component::com_Transform *bT = new Component::com_Transform(posB, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move two boxes towards eachother until collision occurs
		if (posA.x > initPosB.x || posB.x < initPosA.x) {
			std::cout << "No collision detected!" << '\n';
			return false;
		} // end if

		posA.x += 1.0f; // posA = glm::vec3((posA.x + 1.0f), posA.y, posA.z);
		posB.x -= 1.0f; // posB = glm::vec3((posB.x - 1.0f), posB.y, posB.z);

		aT->Position(posA);
		bT->Position(posB);
	} // end while

	std::cout << posA.x << ", " << posA.y << ", " << posA.z << '\n';
	std::cout << posB.x << ", " << posB.y << ", " << posB.z << '\n';

	delete a;
	delete aT;
	delete b;
	delete bT;

	return true;
} // end BoxBox

bool ColliderTest::SphereSphere() {
	// initial positions
	glm::vec3 initPosA = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 initPosB = glm::vec3(10.0f, 0.0f, 0.0f);
	// object a
	Component::com_Sphere* a = new Component::com_Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	glm::vec3 posA = initPosA;
	Component::com_Transform* aT = new Component::com_Transform(posA, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	// object b
	Component::com_Sphere* b = new Component::com_Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	glm::vec3 posB = initPosB;
	Component::com_Transform* bT = new Component::com_Transform(posB, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move two spheres towards eachother until collision occurs
		if (posA.x > initPosB.x || posB.x < initPosA.x) {
			std::cout << "No collision detected!" << '\n';
			return false;
		} // end if

		posA.x += 1.0f;
		posB.x -= 1.0f;

		aT->Position(posA);
		bT->Position(posB);
	} // end while

	delete a;
	delete aT;
	delete b;
	delete bT;

	return true;
} // end SphereSphere

bool ColliderTest::BoxSphere() {
	// initial positions
	glm::vec3 initPosA = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 initPosB = glm::vec3(10.0f, 0.0f, 0.0f);
	// object a
	Component::com_Box* a = new Component::com_Box(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 posA = initPosA; // position of object a
	Component::com_Transform* aT = new Component::com_Transform(posA, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	// object b
	Component::com_Sphere* b = new Component::com_Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	glm::vec3 posB = initPosB;
	Component::com_Transform* bT = new Component::com_Transform(posB, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move a box and a sphere towards eachother until collision occurs
		if (posA.x > initPosB.x || posB.x < initPosA.x) {
			std::cout << "No collision detected!" << '\n';
			return false;
		} // end if

		posA.x += 1.0f; // posA = glm::vec3((posA.x + 1.0f), posA.y, posA.z);
		posB.x -= 1.0f; // posB = glm::vec3((posB.x - 1.0f), posB.y, posB.z);

		aT->Position(posA);
		bT->Position(posB);
	} // end while

	delete a;
	delete aT;
	delete b;
	delete bT;

	return true;
} // end BoxSphere

bool ColliderTest::BoxPlane() {
	// initial positions
	glm::vec3 initPosA = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 initPosB = glm::vec3(10.0f, 0.0f, 0.0f);
	// object a
	Component::com_Box* a = new Component::com_Box(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 posA = initPosA; // position of object a
	Component::com_Transform* aT = new Component::com_Transform(posA, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	// object b
	glm::vec3 vecB = initPosB - initPosA;
	vecB = glm::normalize(vecB);
	Component::com_Plane* b = new Component::com_Plane(vecB, 1.0f);
	glm::vec3 posB = initPosB;
	Component::com_Transform* bT = new Component::com_Transform(posB, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move a box towards a plane until collision occurs
		if (posA.x > initPosB.x) {
			std::cout << "No collision detected!" << '\n';
			return false;
		} // end if

		posA.x += 1.0f;

		aT->Position(posA);
	} // end while

	delete a;
	delete aT;
	delete b;
	delete bT;

	return true;
} // end BoxPlane

bool ColliderTest::SpherePlane() {
	// initial positions
	glm::vec3 initPosA = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 initPosB = glm::vec3(10.0f, 0.0f, 0.0f);
	// object a
	Component::com_Sphere* a = new Component::com_Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	glm::vec3 posA = initPosA;
	Component::com_Transform* aT = new Component::com_Transform(posA, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	// object b
	glm::vec3 vecB = initPosB - initPosA;
	vecB = glm::normalize(vecB);
	Component::com_Plane* b = new Component::com_Plane(vecB, 1.0f);
	glm::vec3 posB = initPosB;
	Component::com_Transform* bT = new Component::com_Transform(posB, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (!a->TestCollision(aT, b, bT).HasCollision()) {
		// move a sphere towards a plane until collision occurs
		if (posA.x > initPosB.x) {
			std::cout << "No collision detected!" << '\n';
			return false;
		} // end if

		posA.x += 1.0f;

		aT->Position(posA);
	} // end while

	delete a;
	delete aT;
	delete b;
	delete bT;

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
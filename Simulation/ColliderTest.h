#pragma once

#include "UnitTest.h"

#include "com_Collider.h"

class ColliderTest : public UnitTest {
public:
	ColliderTest() : UnitTest("Collider Test") {};

	bool Test() override;
private:
	bool BoxBox();
	bool SphereSphere();
	bool BoxSphere();
	bool BoxPlane();
	bool SpherePlane();

};
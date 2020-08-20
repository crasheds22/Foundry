#pragma once

/**
* @class Collision Detection
* @brief placeholder class for interactions between bounding volumes
*
* @author Kristian
*/

#include <glm/glm.hpp>
#include "../Components/Box.h"
#include "../Components/Sphere.h"
#include "../Components/Capsule.h"

class CollisionDetection {
public:

private:
	bool BoxCollision(Box &a, Box &b);
	bool SphereCollision(Sphere &a, Sphere &b);
	//bool CapsuleCollision(Capsule &a, Capulse &b);
	bool BoxSphereCollision(Box &b, Sphere &s);

	// MOVE THIS ELSEWHERE
	float Squaref(float f);
};
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

class CollisionDetection {
public:

private:
	bool BoxCollision(Component::Box &a, Component::Box &b);
	bool SphereCollision(Component::Sphere &a, Component::Sphere &b);
	//bool CapsuleCollision(Capsule &a, Capulse &b);
	bool BoxSphereCollision(Component::Box &b, Component::Sphere &s);

	// MOVE THIS ELSEWHERE
	float Squaref(float f);
};
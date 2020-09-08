#pragma once

/**
* @class Collision Detection
* @brief placeholder class for interactions between bounding volumes
*
* @author Kristian
*/

#include <glm/glm.hpp>

#include "../ECS_core/System.h"

#include "com_Box.h"
#include "com_Sphere.h"

class CollisionDetection : public ECS::System
{
public:

private:
	bool BoxCollision(Component::Box &a, Component::Box &b);
	bool SphereCollision(Component::Sphere &a, Component::Sphere &b);
	//bool CapsuleCollision(Capsule &a, Capulse &b);
	bool BoxSphereCollision(Component::Box &b, Component::Sphere &s);

	// MOVE THIS ELSEWHERE
	float Squaref(float f);
};

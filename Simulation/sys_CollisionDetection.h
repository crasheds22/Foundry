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
	/**
	* @brief detect collision between two boxes
	* 
	* @param Box &a - first of the two boxes to check for a collision between
	* @param Box &b - second of the two boxes to check for a collision between
	*/
	bool BoxCollision(Component::Box &a, Component::Box &b);

	/**
	* @brief detect collision between two spheres
	* 
	* @param Sphere &a - first of the two spheres to check for a collision between
	* @param Sphere &b - second of the two spheres to check for a collision between
	*/
	bool SphereCollision(Component::Sphere &a, Component::Sphere &b);

	//bool CapsuleCollision(Capsule &a, Capulse &b);

	/**
	* @brief detect collision between a box and a sphere
	* 
	* @param Box &b - box to check if it has collided with a sphere
	* @param Sphere &s - sphere to check if it has collided with a box
	*/
	bool BoxSphereCollision(Component::Box &b, Component::Sphere &s);

	// MOVE THIS ELSEWHERE
	/**
	* @brief return float f squared
	* 
	* @param float f - float to square
	* @return float f * f - squared value of f
	*/
	float Squaref(float f);
};

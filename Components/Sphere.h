#pragma once
/**
* @class Sphere
* @brief Sphere bounding volume
* 
* @author Kristian
*/


#include <glm/glm.hpp>

namespace Component
{
	class Sphere 
	{
	public:
		glm::vec3 center; // center point
		float radius; // radius of sphere
	};
}
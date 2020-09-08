#pragma once

/**
* @class Plane
* @brief 
*
* @author Kristian
*/

#include <glm/glm.hpp>

namespace Component
{
	class Plane
	{
	public:
		/**
		* @brief constructs a plane from a vector and a normal vector
		* 
		* @param glm::vec3 v - vector for plane
		* @param glm::vec3 n - normal vector for plane
		*/
		Plane(glm::vec3 v, glm::vec3 n);

		/**
		* @brief constructs a plane from another plane
		* 
		* @param const Plane& p - plane object
		*/
		Plane(const Plane& p);

		/**
		* @brief destructs plane
		* 
		* @post plane is destructed
		*/
		//~Plane(); // don't make empty destructors

	private:
		glm::vec3 vec; /// plane vector
		glm::vec3 normal; /// normal vector
	};
}
#pragma once
/**
* @class Sphere
* @brief Sphere bounding volume
* 
* @author Kristian
*/


#include <glm/glm.hpp>
#include "com_Collider.h"

namespace Component
{
	class Sphere : public Collider
	{
	public:
		/**
		* @brief constructs sphere from center and rad
		* 
		* @param glm::vec3 center - center point of sphere
		* @param float rad - radius of sphere
		*/
		Sphere(glm::vec3 center, float rad);

		/**
		* @brief constructs sphere from sphere object
		* 
		* @param const Sphere& s - sphere object
		*/
		Sphere(const Sphere& s);

		/**
		* @brief destructor
		*/
		~Sphere();

		/**
		* @brief returns center point
		* 
		* @return glm::vec3 center - center point of sphere
		*/
		glm::vec3 Center() const;

		/**/
		void Center(glm::vec3 center);

		float Radius() const;
		void Radius(float radius);

	private:
		glm::vec3 mCenter; // center point
		float mRadius; // radius of sphere
	};
}
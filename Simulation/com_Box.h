#pragma once

/**
* @class Box
* @brief Box bounding volume
*
* @author Kristian
*/

#include <glm/glm.hpp>
#include "com_Collider.h"

namespace Component
{
	class Box : public Collider
	{
	public:
		/**
		* @brief constructs box from min and max
		* 
		* @param glm::vec3 min - minimum point
		* @param glm::vec3 max - maximum point
		*/
		Box(glm::vec3 min, glm::vec3 max);

		/**
		* @brief constructs a box from another box object
		* 
		* @param const Box& b - Box object
		*/
		Box(const Box& b);

		/**
		* @brief destructs box
		* 
		* @post box is destructed
		*/
		//~Box();

		/**
		* @brief returns max
		* 
		* @return glm::vec3 mMax - maximum point
		*/
		glm::vec3 Max() const;

		/**
		* @brief set max
		*
		* @param glm::vec3 max - value to be assigned to max
		*/
		void Max(glm::vec3 max);

		/**
		* @brief returns min
		* 
		* @return glm::vec3 mMin - minimum point
		*/
		glm::vec3 Min() const;

		/**
		* @brief set min
		* 
		* @param glm::vec3 min - value to be assigned to min
		*/
		void Min(glm::vec3 min);

	private:
		glm::vec3 mMin; /// minimum point
		glm::vec3 mMax; /// maximum point
	};
}

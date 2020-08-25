#pragma once

/**
* @class Box
* @brief Box bounding volume
*
* @author Kristian
*/

#include <glm/glm.hpp>

namespace Component
{
	class Box 
	{
	public:
		Box(glm::vec3 min, glm::vec3 max);
		Box(const Box& b);
		~Box();

		glm::vec3 Max() const;
		void Max(glm::vec3 max);
		glm::vec3 Min() const;
		void Min(glm::vec3 min);

	private:
		glm::vec3 mMin; // minimum point
		glm::vec3 mMax; // maximum point
	};
}

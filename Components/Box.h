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
		glm::vec3 min; // minimum point
		glm::vec3 max; // maximum point
	};
}

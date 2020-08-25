#include "Box.h"

namespace Component
{
	Box::Box(glm::vec3 min, glm::vec3 max) : min(min), max(max)
	{
	}

	Box::Box(const Box& b) : min(b.min), max(b.max)
	{
	}
	
	Box::~Box()
	{
	}
	
	glm::vec3 Box::Max() const
	{
		return max;
	}

	void Box::Max(glm::vec3 newMax)
	{
		max = newMax;
	}
	
	glm::vec3 Box::Min() const
	{
		return min;
	}

	void Box::Min(glm::vec3 newMin)
	{
		min = newMin;
	}
}

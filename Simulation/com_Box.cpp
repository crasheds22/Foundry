#include "com_Box.h"

namespace Component
{
	Box::Box(glm::vec3 min, glm::vec3 max) : mMin(min), mMax(max)
	{
		Type(ColliderType::BOX);
	}

	Box::Box(const Box& b) : mMin(b.mMin), mMax(b.mMax)
	{
		Type(ColliderType::BOX);
	}
	
	/* Box::~Box()
	{
	} */
	
	glm::vec3 Box::Max() const
	{
		return mMax;
	}

	void Box::Max(glm::vec3 max)
	{
		mMax = max;
	}
	
	glm::vec3 Box::Min() const
	{
		return mMin;
	}

	void Box::Min(glm::vec3 min)
	{
		mMin = min;
	}
}

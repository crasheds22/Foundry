#ifndef __PROTO_COLLIDER_H__
#define __PROTO_COLLIDER_H__

#include "IPrototype.h"

namespace Prototype
{
	class Collider
		: public IPrototype
	{
	public:
		Collider(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax, int type);

		~Collider();

	private:

	};
}

#endif

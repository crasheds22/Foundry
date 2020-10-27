#ifndef __PROTO_COLLIDER_H__
#define __PROTO_COLLIDER_H__

#include "IPrototype.h"

namespace Prototype
{
	class Collider
		: public IPrototype
	{
	public:
		Collider(std::string name, Component::com_Transform transform, glm::vec3 Max, glm::vec3 Min, int type);

		~Collider();

	private:

	};
}

#endif

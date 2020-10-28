#ifndef __PROTOTYPE_FACTORY_H__
#define __PROTOTYPE_FACTORY_H__

#include "IPrototype.h"
#include "Prototypes.h"

#include "Components/com_Transform.h"

namespace Prototype
{
	class Factory
	{
	public:
		static IPrototype* Make(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);
	};
}

#endif
